<?PHP
/*
    Nombre: operador.php
    Autor: Julio Tuozzo
    Función: Controlador de administración de operadores del sistema
    Function: Sistem operators administration controller.
    Ver: 2.12
*/

session_start();
require('config.inc.php');
require($Include.'lang.inc');

if ($_SESSION['PHD_NIVEL']<20)
    {require($Include.'login.inc');
     exit();
    }

require('funciones.inc.php');

## Depuro los GETs
// GETs sanitization

if (get_magic_quotes_gpc())
    { foreach($_GET as $clave => $valor)
      {$_GET[$clave]=stripslashes($_GET[$clave]);
      }
    }

foreach($_GET as $clave => $valor)
     {$_GET[$clave]=trim(htmlentities($_GET[$clave],ENT_QUOTES,"ISO-8859-1"));
     }


$mensaje='<br />';
$private_check="checked";
$avisar_solicitud_check=$avisar_asignado_check="";

if (isset($_GET[orden]))
    {$orden=$_GET[orden];
    }
else
    {$orden="sector_id, operador_id";
    }
$sentido=$_GET['sentido'];
$q_registros=$_GET['q_registros'];
$pagina=$_GET['pagina'];


## Me conecto con la base de datos
// Connect with the database

    $Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
    $Uso=mysql_select_db($Base) or die (mysql_error());


## Verifico que no se haya "posteado" el formulario, en caso de ser así, veo
## cuál fue la opción que se clickeó.
// Check that the form has not been post, in case of being thus, see
// which was the select option.

    if (isSet($_POST[$Save]))
	   {require($Include.'opr_ins.inc');
   	    }
    elseif (isSet($_POST['salir']))
	   { unset($_SESSION['OPERADOR']);
         header("Location: index.php");
   	    }
    elseif (isSet($_POST[$Modif]))
	   {require($Include.'opr_mod.inc');
   	    }
    elseif (isSet($_POST['modificar']))
        {require($Include.'opr_select.inc');
        }
    elseif (isSet($_POST['genero']))
        {require($Include.'opr_gen_clave.inc');
        }
    elseif (isSet($_POST['cancelar']))
        {// Blanqueo variables
         $_20=$_10=$_0=$e_mail=$ape_y_nom=$operador='';}



## Formulario de ingreso de datos del operador.
// Operator data input form.

require($Include.'operador.inc');
?>

