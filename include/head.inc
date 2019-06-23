<?PHP
/*
    Nombre: head.inc
    Autor: Julio Tuozzo
    Función: HEAD de las páginas
    Function: Page's Head.
    Ver: 1.43

*/
header('Content-Type: text/html; charset=ISO-8859-1');
//print_r($_SESSION); 
//if(!isset($_SESSION[PHD_SECTOR_ID])){
//  $_SESSION[PHD_SECTOR_ID] = 1;
//}
//print_r($_SESSION); 
echo
"<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='es' lang='es'>
<head>
    <meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>

  <title>Help Desk &nbsp; ($_SESSION[PHD_OPERADOR]) - $_SESSION[PHD_APE_Y_NOM] / $_SESSION[PHD_SECTOR_ID] </title>
  <LINK REL=STYLESHEET TYPE='text/css' HREF='phd.css' TITLE='estilo'>
  <link rel='shortcut icon' href='favicon.ico' />
  $frames
</head> \n";

?>
