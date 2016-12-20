<?php

    // configuration
    require("../includes/config.php"); 

    // query database for user
    $rows = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
    //$cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    //if (count($cash) == 1)
    //    {
    //        // first (and only) row
    //        $cash1 = $cash[0]["cash"];
    //    }
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "transaction" => $row["transaction"],
                "time" => $row["time"]
            ];
        }
    }
    // render portfolio
    render("history.php", ["title" => "History", "positions" => $positions]);

?>
