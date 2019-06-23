<?PHP
/*
    Nombre: set_atrib.php
    Autor: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Función: Inicialice some PHD Help Desk attributes
    Ver: 2.12
*/

session_start();
require('../../config.inc.php');
require('../../include/lang.inc');

if (!isset($_SESSION['ATRIB']))

    {include('setup_head.inc');
     echo "<p class='danger'>INVALID CALL</p>";
     exit();
    }


// Armo la matriz de valores de atributos

$v_clases=array("$Contact","$State","$Process","$Type");
$v_atributo[0]=array("Personal","Phone","E-mail");
$v_atributo[1]=array("Pending","Closed","Canceled");
$v_atributo[2]=array("Service Desk","On Site");
$v_atributo[3]=array("Hardware","Software","Aplications","Qualification","Local net","E-mail","Internet");


if (!isset($_POST[b_atrib]))
    {require('set_atrib.inc');
     exit();
    }

if(!mysql_connect($Host,$Usuario,$Contrasena) or !mysql_select_db($Base))
    {$mensaje="<h2 class='danger'>Database conexion error.</h2>
     MySQL error message: ".mysql_error();
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
              ("<h2 class='danger'>Error - Fail insert data in the table atributo.</h2>
               MySQL error message: ".mysql_error());
            }
        }
    }

$path_phd_inc="";
$a_include = explode( PATH_SEPARATOR, ini_get('include_path') );
$a_long=count($a_include);

for ($I=0; $I<$a_long; $I++)
    {$f_path=str_replace("\\","/",$a_include[$I]);
     if (substr($f_path,-1)!='/')
        {$f_path.='/';
        }
     if (is_readable($f_path."phd.inc"))
        {$path_phd_inc=$f_path;
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
