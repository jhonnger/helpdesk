<?PHP
/*
    Nombre: usuario.php
    Autor: Julio Tuozzo
    Función: Controlador de administración de usuarios de los casos
    Function: Administration of ticket's users controller
    Ver: 2.12
*/

session_start();
require('config.inc.php');
require($Include.'lang.inc');
require('funciones.inc.php');

if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<20)
    {require($Include.'login.inc');
     exit();
    }

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


## Inicializo $mensaje que es donde voy a colocar los mensajes de error en caso de existir, inicializo las variables que vienen por GET.
// Inicializing $mensaje that is where I am going to place the messages of error in case of existing.

$mensaje='<br />';
$active_check="checked";

if (isset($_GET[orden]))
    {$orden=$_GET[orden];
    }
else
    {$orden="usuario_id";
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

    if (isset($_POST['guardar']))
	   {require($Include.'user_insert.inc');
   	   }
    elseif (isset($_POST['modificar']))
	   {require($Include.'user_modif.inc');
   	   }
    elseif (isset($_POST['usr_modificar']))
        {require($Include.'user_select.inc');
        }
    elseif (isset($_POST['genero']))
        {require($Include.'usr_gen_clave.inc');
        }
    elseif (isset($_POST['salir']))
	   { unset($_SESSION['USUARIO']);
         header("Location: index.php");
       }

## Formulario de ingreso de datos del usuario.
// User data input form.

require($Include.'usuario.inc');
?>

