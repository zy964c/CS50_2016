<?php

    // configuration
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        $rows_all = CS50::query("SELECT * FROM portfolio WHERE user_id = ?", $_SESSION["id"]);
        if (count($rows_all) == 0)
        {
            // first (and only) row
            render("sell_sorry.php");
        }
        $positions = [];
        foreach ($rows_all as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"]
                ];
            }
        }
        // render sell
        render("sell.php", ["title" => "Sell", "positions" => $positions]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must choose stock to sell.");
        }
        
        
    }
    // query database for user
    
    $rows_stock = CS50::query("SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);

        
    $positions1 = [];
    //$stock1 = lookup($_POST["symbol"]);
    foreach ($rows_stock as $row)
    {
            $stock1 = lookup($row["symbol"]);
            if ($stock1 !== 0)
            {
                $positions1[] = [
                    "name" => $stock1["name"],
                    "price" => $stock1["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"]
                ];
            }
    }

    $price_sum = ($positions1[0]["price"]*$positions1[0]["shares"]);

    CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $price_sum, $_SESSION["id"]);
    $rows = CS50::query("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
    CS50::query("INSERT INTO history (user_id, symbol, shares, transaction, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], strtoupper($_POST["symbol"]), $positions1[0]["shares"], "SELL", $positions1[0]["price"]);
    redirect("index.php");

?>
