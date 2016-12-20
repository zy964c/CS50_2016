<?php
    // configuration
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("deposit.php");
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["summ"]))
        {
            apologize("You must provide a summ to deposit.");
        }
        else if ($_POST["summ"] < 0)
        {
            apologize("You must provide positive decimal number in summ input field.");
        }
    }


    //CS50::query("INSERT INTO portfolio (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
    CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["summ"], $_SESSION["id"]);
    //CS50::query("INSERT INTO history (user_id, symbol, shares, transaction, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"], "BUY", $data["price"]);
    
    redirect("index.php");
?>
