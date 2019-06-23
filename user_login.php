<?PHP
/*
    Nombre: user_login.php
    Autor: Julio Tuozzo
    Función: Validación de usuario y contraseña.
    Function: user and password validation.
    Ver: 2.12
    
*/
session_start();
## Blanqueo variables globales.
// Unset global variables.

foreach($_SESSION as $clave => $valor)
     { $hay_phd=strpos("AUX".$clave,"PHD_");
       if($hay_phd)
            {unset($_SESSION[$clave]);
            }
     }

require('config.inc.php');
require($Include.'lang.inc');
require('funciones.inc.php');
require('./securimage/securimage.php');



$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

## Busco los parámetros de la aplicación e inicializo las variables globales.
// Search the software parameters and initialize the global variables.

$query="SELECT * FROM {$MyPHD}parametros";
$result=mysql_query($query) or die(mysql_error());
$q_filas=mysql_num_rows($result);

if($q_filas!=1)
	{$mensaje=str_replace("%1%", $q_filas,$Err_parameters_file);
	 include('user_login.inc');
	 exit();
    }

$row=mysql_fetch_array($result);

$_SESSION['PHD_MAX_ATTACH']=$row['max_attach'];
$_SESSION['PHD_FROM_USER_REQUEST']=$row['from_user_request'];
$_SESSION['PHD_MAX_LINES_SCREEN']=$row['max_lines_screen'];
$_SESSION['PHD_PEN']=$row['PEN'];
$_SESSION['PHD_PAS']=$row['PAS'];
$_SESSION['PHD_CAN']=$row['CAN'];
$_SESSION['PHD_ATE']=$row['ATE'];
$_SESSION['PHD_DATE_FORMAT']=$row['date_format'];

## Pregunto si pidió generar la contraseña
// Ask about the password generation

if(isset($_POST['genera']))
    {require($Include.'usr_self_clave.inc');
    }

## Verfico que se haya ingresado por "submit", si no es así
## pido usuario y contraseña
// Check that has been entered by “submit”, if it is not thus
// request user and password

if(!isSet($_POST['submit']))
	  {include($Include.'user_login.inc');
	   exit();
      }
    
if (strlen($_POST['usuario'])==0)        ## Verifico que haya ingresado el usuario.
	   {$mensaje=$No_user;                   // Verify that the user has entered.
    	 include($Include.'user_login.inc');
    	 exit();
    	}

$usuario=trim(strip_tags($_POST['usuario']));
if (strlen($_POST[contrasenia])==0) ## Verifico que haya ingresado al contraseña.
	{$mensaje=$Err_input_passwd;        // Verify that the password has entered.
	 include($Include.'user_login.inc');
	 exit();
	}

## Busco el usuario en la tabla correspondiente
// Search the user in the table

$query="SELECT * FROM {$MyPHD}usuario WHERE usuario_id='$usuario'";
$result=mysql_query($query) or die(mysql_error());
$q_filas=mysql_num_rows($result);

if($q_filas!=1)
	   {$mensaje=$User_not_exists;
	    include($Include.'user_login.inc');
	    exit();
	   }

### Ahora verifico la contraseña
$md5_contrasenia=md5($_POST['contrasenia']);


$query="SELECT us.*, ar.nombre
        FROM {$MyPHD}usuario us
        JOIN {$MyPHD}area ar ON ar.area_id=us.area_id
        WHERE usuario_id='$usuario' AND contrasenia='$md5_contrasenia'";
        
$result=mysql_query($query) or die (mysql_error());;
$q_filas=mysql_num_rows($result);
if ($q_filas!=1)
   	    {$mensaje=$Invalid_passwd;
	    include($Include.'user_login.inc');
	    exit();
	    }

$row=mysql_fetch_array($result);
if ($row['activo']!="S")
		{$mensaje=$Inactive_user;
         include($Include.'user_login.inc');
		 exit();
		}


## usuario y contraseña válidos, asigno nivel de acceso 4
// User and password valid, assign access level 4

$_SESSION['PHD_OPERADOR']=$row['usuario_id'];
$_SESSION['PHD_APE_Y_NOM']=$row['ape_y_nom'];
$_SESSION['PHD_AREA_ID']=$row['area_id'];
$_SESSION['PHD_AREA_NOMBRE']=$row['nombre'];
$_SESSION['PHD_PISO']=$row['piso'];
$_SESSION['PHD_TELEFONO']=$row['planta'];
$_SESSION['PHD_E_MAIL']=$row['e_mail'];


## Verifico si hay que obligar el cambio de contraseña.
// Check the change password.

if($row['cambia_clave']=="S")
        {$_SESSION['PHD_NIVEL']=3;
         header("Location: user_clave_chg.php"); // Voy al cambio de contrseña.
        }
else
        {$_SESSION['PHD_NIVEL']=4;
         header("Location: user_request.php"); // Todo OK, voy a la solicitud de usuario
        }

	
?>
