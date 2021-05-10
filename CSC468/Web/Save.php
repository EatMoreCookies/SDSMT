<?php
function save($head, $larm, $body, $rarm, $legs){

    if( !isset($_COOKIE['savedfile']))
        setcookie('savedfile', 0);

    else{
        $val = (int)$_COOKIE["savedfile"];
        setcookie('savedfile', $val + 1);
    }

    $newFile = 'character_'.$_COOKIE['savedfile'].".txt";

    $myfile = fopen("uploads/".$newFile, "w'");
    fwrite($myfile, $head."\n");
    fwrite($myfile, $larm."\n");
    fwrite($myfile, $body."\n");
    fwrite($myfile, $rarm."\n");
    fwrite($myfile, $legs);
    fclose($myfile);
}
?>

