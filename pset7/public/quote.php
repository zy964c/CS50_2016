<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide stock symbol.");
        }

        $data = lookup($_POST["symbol"]);
        if ($data == 0)
        {
            apologize("No stock found with such name in database.");
        }
        else
        {
            render("quote.php", ["symbol" => $data["symbol"], "name" => $data["name"], "price" => $data["price"]]);
        }
    }
?>