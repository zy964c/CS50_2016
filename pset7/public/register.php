<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must provide confirmation of your password.");
        }
        //validate that password matches confirmation
        else if ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Your password must match confirmation field.");
        }
        
        //add user to the db
        $result = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 0)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        if ($result == 0)
        {
            apologize("User with the same usernabe is already in database, please choose a different username.");
        }
        else
        {
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            // remember that user's now logged in by storing user's ID in session
            $_SESSION["id"] = $id;
            // redirect to portfolio
            redirect("/index.php");
        }
    }

?>