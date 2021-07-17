import os
import re

from cs50 import SQL
from datetime import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get cash number
    temp = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = temp[0]["cash"]

    # group by and SUM() to combine stocks by symbol
    shares = db.execute("SELECT stockname, symbol, SUM(number) FROM purchase WHERE id = ? GROUP BY id, symbol", session["user_id"])

    # start totalling
    grandTotal = cash

    # assigning current prices to stocks and updating
    for each in shares:
        quote = lookup(each["symbol"])
        each["name"] = quote["name"]
        each["stockprice"] = quote["price"]
        each["total"] = each["stockprice"] * each["SUM(number)"]
        each["number"] = each["SUM(number)"]
        grandTotal += each["total"]

    return render_template("index.html", shares=shares, cash=cash, grandTotal=grandTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # input checks
        if not request.form.get("symbol"):
            return apology("Symbol required")
        if lookup(request.form.get("symbol")) == None:
            return apology("invalid symbol")

        shares = request.form.get("shares")

        if not shares:
            return apology("Enter a number of shares")

        # not parsing shares, in order to check if fractional using the isdigit function.
        if not shares.isdigit():
            return apology("Invald number of shares")

        if int(shares) <= 0:
            return apology("Number of shares must be a positive number")

        stock = lookup(request.form.get("symbol"))

        price = int(shares) * float(stock["price"])

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        newCash = cash[0]["cash"] - price

        if cash[0]["cash"] < price:
            return apology("Insufficient funds")

        # insert purchase
        db.execute("INSERT INTO purchase (id, stockname, stockprice, date, symbol, number) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], stock["name"], price, datetime.now(), stock["symbol"], int(shares))

        # update cash
        db.execute("UPDATE users SET cash = ? WHERE id=?", newCash, session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    shares = db.execute("SELECT stockname, symbol, number, stockprice, date FROM purchase WHERE id = ?", session["user_id"])

    return render_template("history.html", shares=shares)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stock = request.form.get("symbol")

        if not stock:
            return apology("No stock symbol found", 400)

        # API to get stock info
        quote = lookup(stock)

        if quote == None:
            return apology("Invalid symbol", 400)

        return render_template("quoted.html", value=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")

        # checks
        if not request.form.get("username"):
            return apology("Invalid username", 400)

        if username == db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("Username already taken", 400)

        password = request.form.get("password")

        if not request.form.get("password"):
            return apology("Invalid password", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 400)

        # extra implementation of password requirements
        if len(password) < 8:
            return apology("Password must contain at least 8 characters")

        if not re.search('\d', password):
            return apology("String must contain at least one digit")

        hashpass = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashpass)

            rows = db.execute("SELECT * FROM users WHERE username = ?", username)

            # Remember which user has logged in
            session["user_id"] = rows[0]["id"]

        except:
            # If the username already exists.
            return apology("Username already in use", 400)

        # If all successful redirect user to home page
        return redirect("/")

    # user reached route via get (clicking a link)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")

        number = int(request.form.get("shares"))

        if number < 1:
            return apology("Number of shares must be a positive integer")

        current = db.execute("SELECT SUM(number) FROM purchase WHERE id = ? AND symbol = ? GROUP BY id, symbol",
                             session["user_id"], symbol)

        print(current[0]["SUM(number)"])

        # if user does not have enough shares
        if int(current[0]["SUM(number)"]) < number:
            return apology("You don't have that many shares")

        sale = lookup(symbol)

        if sale == None:
            return apology("Invalid stock symbol")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # print(cash[0]["cash"])
        print(sale)

        # new cash value after returns from sale
        newCash = (sale["price"] * number) + int(cash[0]["cash"])

        db.execute("UPDATE users SET cash = ? WHERE id=?", newCash, session["user_id"])

        # insert record of the sale
        db.execute("INSERT INTO purchase (id, stockname, stockprice, date, symbol, number) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], sale["name"], sale["price"], datetime.now(), sale["symbol"], -number)

        return redirect("/")

    else:
        # get data to fill select element
        shares = db.execute("SELECT symbol FROM purchase WHERE id = ? GROUP BY symbol", session["user_id"])

        return render_template("sell.html", shares=shares)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
