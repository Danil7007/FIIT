<?php
session_start();
$lang = $_GET["lang"];
if($lang == "sk"){
    $lang = "en";
}
elseif($lang == "en"){
    $lang = "sk";
}
$_SESSION["lang"] = $lang;
if(isset($_REQUEST["destination"])){
    header("Location: {$_REQUEST["destination"]}");
}else if(isset($_SERVER["HTTP_REFERER"])){
    header("Location: {$_SERVER["HTTP_REFERER"]}");
}else{
     /* some fallback, maybe redirect to index.php */
}
?>