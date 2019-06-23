<?PHP
/*
    Nombre: set_atrib.php
    Autor: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Función: Inicializa algunos atributos de PHD Help Desk
    Ver: 1.12
*/

session_start();
require('../../config.inc.php');
require('../../include/lang.inc');

if (!isset($_SESSION['ATRIB']))

    {include('setup_head.inc');
     echo "<p class='danger'>LLAMADA INVALIDA</p>";
     exit();
    }


// Armo la matriz de valores de atributos

$v_clases=array("$Contact","$State","$Process","$Type");
$v_atributo[0]=array("Personal","Telefono","E-mail");
$v_atributo[1]=array("Pendiente","Terminado","Cancelado");
$v_atributo[2]=array("Help Desk","On Site");
$v_atributo[3]=array("Hardware","Software de base","Aplicaciones","Capacitacion","Red","E-mail","Internet");


if (!isset($_POST[b_atrib]))
    {require('set_atrib.inc');
     exit();
    }

if(!mysql_connect($Host,$Usuario,$Contrasena) or !mysql_select_db($Base))
    {$mensaje="<h2 class='danger'>Error de conexi&oacute;n con la base de datos.</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_atrib.inc');
     exit();
    }


for($I=0;$I<4;$I++)
    {$qJ=count($v_atributo[$I]);
     for ($J=0;$J<$qJ;$J++)
        {$in_name="in_".$v_atributo[$I][$J];
         $in_name=str_replace(" ","_",$in_name);
          if ($_POST[$in_name]==1)
            {$query="INSERT INTO atributo
              VALUES (NULL,'$v_clases[$I]','{$v_atributo[$I][$J]}','S','SETUP',NOW(),'SETUP',NOW())";
              $create=mysql_query($query) or die
              ("<h2 class='danger'>Error en la ejecuci&oacute;n del script de
               insert de datos en tabla atributo</h2>".mysql_error());
            }
        }
    }


$a_caso = implode('', file("../../config.inc.php"));
$a_caso=str_replace("\$PHD_Ins='NO';","",$a_caso);
$fp = fopen ("../../config.inc.php", "w+");
fwrite($fp,$a_caso);
fclose($fp);


session_destroy();
header("Location: index.php");
?>
