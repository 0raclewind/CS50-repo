import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, sanitize

os.environ["API_KEY"] = 'JPJJ4M180WH7DV59'
# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = db.execute('SELECT * \
                        FROM users \
                        WHERE id = :id', id=session["user_id"])[0]

    db_shares = db.execute('SELECT * \
                        FROM purchases \
                        WHERE owner = :user', user=user["username"])
    shares = []
    total = 0

    for share in db_shares:
        price = lookup(share["symbol"])["price"]
        total += price * share["amount"]
        shares.append({
            "symbol": share["symbol"],
            "price": price,
            "amount": share["amount"]
        })

    count = len(shares)
    return render_template("home.html",
                           shares=shares,
                           count=count,
                           user=user,
                           usd=usd,
                           total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    message = ""
    if request.method == 'POST':
        symbol = sanitize(request.form.get("symbol")).upper()
        stock_check = lookup(symbol)
        shares = int(sanitize(request.form.get("shares")))
        username = db.execute('SELECT username \
                                FROM users \
                                WHERE id = :id', id=session["user_id"])[0]["username"]
        cash = db.execute('SELECT cash \
                            FROM users \
                            WHERE username = :user',
                          user=username)[0]["cash"]
        if stock_check == None:
            return apology("Stock not found")
        else:
            total_price = shares * stock_check["price"]

        if symbol == '' or shares == '':
            return apology("Fields cannot be blank")
        elif shares < 1:
            return apology("Shares amount has to be positive number")
        elif total_price > cash:
            return apology("Not enough money")
        else:
            owned = db.execute("SELECT amount \
                                FROM purchases \
                                WHERE owner = :user \
                                AND \
                                symbol = :symbol",
                               user=username,
                               symbol=symbol)
            if owned:
                db.execute("UPDATE purchases \
                            SET amount = :shares \
                            WHERE owner = :user \
                            AND symbol = :symbol",
                           shares=shares + owned[0]["amount"],
                           user=username,
                           symbol=symbol)
            else:
                db.execute('INSERT INTO purchases (symbol, amount, owner) \
                            VALUES (:symbol, :amount, :user)',
                           symbol=symbol,
                           amount=shares,
                           user=username)

            db.execute('UPDATE users \
                        SET cash = :cash \
                        WHERE username = :user',
                       cash=round(cash - total_price, 2),
                       user=username)
            message = "You successfuly bought %i shares of %s for %s" % (shares, symbol, usd(total_price))
            return redirect(url_for("index", message=message))
    return render_template("buy.html", message=message)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=sanitize(request.form.get("username")))

        # Ensure username exists and password is correct
        password = sanitize(request.form.get("password"))
        hash_check = check_password_hash(rows[0]["hash"], password)
        if len(rows) != 1 or not hash_check:
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
    symbol = ""
    price = 0
    if request.method == "POST":
        if request.form.get("symbol") != "":
            stock = lookup(sanitize(request.form.get("symbol")))
            if not stock:
                return apology("Not found")
            else:
                price = usd(stock["price"])
                symbol = stock["symbol"]
        else:
            return apology("Field cannot be blank")
    return render_template("quote.html", symbol=symbol, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        username = sanitize(request.form.get("username"))
        password = sanitize(request.form.get("password"))
        password_repeat = sanitize(request.form.get("confirmation"))
        if username == '' or password == '' or password_repeat == '':
            return apology("Fields cannot be blank.")
        elif password != password_repeat:
            return apology("Passwords didn't match.")
        else:
            user = db.execute('SELECT * \
                                FROM users \
                                WHERE username = :user', user=username)
            if user:
                return apology("User already exists.")
            else:
                user_id = db.execute('INSERT INTO users (username, hash) \
                                    VALUES (:username, :hash)',
                                     username=username,
                                     hash=generate_password_hash(password))
                # session["user_id"] = user_id
                message = "Account has been created"
                return redirect(url_for("login", message=message))

    else:
        return render_template('register.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user = db.execute('SELECT username, cash \
                        FROM users \
                        WHERE id = :id', id=session["user_id"])[0]
    shares = db.execute('SELECT symbol, amount \
                        FROM purchases \
                        WHERE owner = :owner', owner=user["username"])

    print(shares)
    return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
