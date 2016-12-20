<table class="table table-striped">


    <!--<iframe allowfullscreen frameborder="0" height="315" src="https://www.youtube.com/embed/oHg5SJYRHA0?autoplay=1&iv_load_policy=3&rel=0" width="420"></iframe>
    -->
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
        <?php foreach ($positions as $position): ?>
            <tr>
                <td align="left"><?= $position["symbol"] ?></td>
                <td align="left"><?= $position["name"] ?></td>
                <td align="left"><?= $position["shares"] ?></td>
                <td align="left"><?= $position["price"] ?></td>
                <td align="left"><?= ($position["price"] * $position["shares"]) ?></td>
            </tr>
        <?php endforeach ?>
        <tr>
            <td align="left">CASH</td>
            <th></th>
            <th></th>
            <th></th>
            <td align="left"><?= $cash ?></td>
        </tr>
</table>

