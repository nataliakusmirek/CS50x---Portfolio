import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# NOTE! Many html's are based on the notes from CS50 Lecture 9, (especially the tables, those were tough to get at first.)


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
    # User $$ total
    ucash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    # Get user's stock --- NOTE! format was based on the notes given for Index on the Finance assignment page.
    # Porfolio header was from https://cs50.stackexchange.com/questions/30264/pset7-finance-index.
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM portfolio WHERE id=:id GROUP BY symbol HAVING total_shares > 0", id=session["user_id"])

    cash = ucash[0]['cash']
    utotal = cash

    for stock in stocks:
        symbol = stock['symbol']
        share_num = int(stock['shares'])
        quote = lookup(symbol)
        price = float(quote['price_per_share'])
        stock_value = float(price * share_num)
        utotal += stock_value
    return render_template("index.html", stocks=stocks, cash=cash, total=utotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Provide a valid symbol.", 400)

        elif int(request.form.get("shares")) <= 0:
            return apology("Provide a positive integer.", 400)

        # Check current stocks
        stock = lookup(request.form.get("stock"))
        if stock == None:
            return apology("Stock symbol isn't valid.", 400)

        # Get cost
        cost = int(request.form.get("shares")) * stock['price']
        if cost > result[0]["cash"]:
            return apology("You don't have enough cash for this! Sorry! :(", 400)

        # Update User' cash
        db.execute("UPDATE users SET cash=cash-:cost WHERE id=:id", cost=cost, id=session["user_id"])

        db.execute("INSERT INTO transactions (user_id, stock, quantity, price, date) VALUES (?, ?, ?, ?, ?)")

        # Get that share from the portfolio
        portfolio = db.execute("SELECT quantity FROM transactions WHERE stock=:stock", stock=quote["symbol"])

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Select transactions from user portfolio!
    portfolio = db.execute("SELECT stock, quantity, price, date FROM transactions WHERE user_id=:id", id=session["user_id"])

    if not portfolio:
        return apology("No transacations found. Sorry! :(")
    return render_template("history.html", stocks=portfolio)


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
    stock = request.form.get("symbol")
    if request.method == "POST":
        if not stock:
            return apology("Provide stock symbol.")
        quote = lookup(stock)
        if quote == None:
            return apology("Not a valid stock symbol, try again.")
        else:
            return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if not username:
            return apology("Username not provided.", 400)
        elif len(rows) != 0:
            return apology("Username already exists.", 400)
        elif not password:
            return apology("Password not provided.", 400)
        elif not confirmation == password:
            return apology("Password does not match.", 400)
        else:
            # Hash the password, format taken from werkzeug documentation website
            hash = generate_password_hash(password, method="pbkdf2:sha256", salt_length=8)
            # Add user to db!
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not symbol:
            return apology("Please select a stock.")
        if shares <= 0:
            return apology("Please provide a valid share amount.")
        if not shares:
            return apology("Share not found. Sorry! :(")
        return redirect("/")
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
