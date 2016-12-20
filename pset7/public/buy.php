<?php
    // configuration
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy.php");
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must choose stock to buy.");
        }

        else if (empty($_POST["shares"]))
        {
            apologize("You must choose how many stocks to buy.");
        }
        else if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("You must provide positive integer in shares input field.");
        }
    }
    
    $data = lookup($_POST["symbol"]);
    if ($data == 0)
        {
            apologize("No stock found with such name in database.");
        }

    $price_sum = ($data["price"]*$_POST["shares"]);
    $available_cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    if ($price_sum > $available_cash[0]["cash"])
    {
        render("buy_sorry.php");
    }

    CS50::query("INSERT INTO portfolio (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
    CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $price_sum, $_SESSION["id"]);
    CS50::query("INSERT INTO history (user_id, symbol, shares, transaction, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"], "BUY", $data["price"]);
    
    redirect("index.php");
?>
