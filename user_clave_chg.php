<?PHP
/*
    Nombre: user_clave_chg.php
    Autor: Julio Tuozzo
    Función: Cambio de clave de usuario.
    Funcition: user change password.
    Ver: 2.12
*/

## Verifico que se encuentre validado el usuario, si no es asi lo
## dirijo a la pantalla de login.
// Verify that one is validated the user, if it is not therefore
// redirect to the screen of login.

session_start();
require('config.inc.php');
require($Include.'lang.inc');


if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']>4)
    {require($Include.'user_login.inc');
     exit();
    }
## Verifico si entró por expiración de contraseña para colocar
## el mensaje correspondiente
// Verify if the password was expired to place the corresponding message.

elseif ($_SESSION['PHD_NIVEL']<4)
   {$mensaje=$Pswd_expired;
    }
## Verifico que no haya cancelado, si es así vuelve al index
// Check that it has not cancelled, if it is thus returns to index.

if (isset($_POST['salir']))
    {header("Location: user_request.php");
    }

## Verfico que se haya ingresado por "submit"", si es así resto
## uno a la cantidad de intentos, si es menor a cinco mato la sesión
## y voy a la pantalla de login, si no es así
## coloco la pantalla que pide el cambio de clave e inicializo
## la variable que cuenta los intentos de cambio.
// Verfy that has entered by “submit "", if  one to the amount on attempts
// is thus rest, if is lower to five, kills the session and goes to the screen
// of login, if he is not thus change to the screen that requests the change of
// key and initialize the variable that counts the attempts of change.

if(isSet($_POST['cambiar']))
    {$_SESSION['PHD_INTENTOS']=$_SESSION['PHD_INTENTOS']-1;
     if ($_SESSION['PHD_INTENTOS']<0)
        {session_destroy();
         header("Location: user_request.php");
        }
    }
else
	{$_SESSION['PHD_INTENTOS']=5;
     require($Include.'clave_chg.inc');
	 exit();
	}

## Me conecto con la base de datos.
// Connect to the database.

$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());



## Valido que la nueva contraseña y su reingreso sean iguales
// Check that the new password and re type are equal

if ($_POST[nueva]!= $_POST[reingresa])
    {$mensaje=$Pswd_not_equal;
     require($Include.'clave_chg.inc');
     exit();
    }

## asigno la nueva contraseña y valido que sean letras y/o números
// Assign the new password and check that is letters and/or numbers

$nueva=$_POST[nueva];

if(!preg_match('#^[a-zA-Z0-9]+$#', $nueva))

   {$mensaje=$Pswd_only_ln;
     require($Include.'clave_chg.inc');
     exit();

    }


## Verifico que la nueva contraseña no tenga más de tres letras/números repetidos
// Chack that the new password does not have more than three repeated letters/numbers

foreach (count_chars($nueva, 1) as $cantidad)
    {if ($cantidad>3)
        {$mensaje=$Pswd_repeat_d;
         require($Include.'clave_chg.inc');
         exit();
        }
    }


## Valido que por lo menos tenga seis dígitos
## Check that at least has six digits

if (strlen($nueva)<6)
   {$mensaje=$Pswd_six_d;
     require($Include.'clave_chg.inc');
     exit();

    }

## Valido que el usuario y la contraseña sean distintos
// Check that the user and the password are different

if ($nueva==$_SESSION[PHD_OPERADOR])
   {$mensaje=$Pswd_same_user;
     require($Include.'clave_chg.inc');
     exit();

    }


## Verifico la contraseña anterior
// verify the previous password

$md5_actual=md5($_POST['actual']);

$query="SELECT * FROM {$MyPHD}usuario WHERE usuario_id='$_SESSION[PHD_OPERADOR]' AND contrasenia='$md5_actual'";
$result=mysql_query($query);
$q_filas=mysql_num_rows($result);
if ($q_filas<1)
    {$mensaje=$Invalid_passwd;
     require($Include.'clave_chg.inc');
     exit();
    }

## Verifico que la anterior y la nueva no sean iguales
// Verify that previous and the new one is not equal

if ($_POST[actual]==$nueva)
    {$mensaje=$Pswd_same_act;
     require($Include.'clave_chg.inc');
     exit();
    }

## Todo OK, actualizo la nueva contraseña
// All OK, update the new password.

$md5_nueva=md5($nueva);

$query="UPDATE {$MyPHD}usuario SET
        contrasenia='$md5_nueva',
        cambia_clave='N',
        update_user='{$_SESSION['PHD_OPERADOR']}',
        update_datetime=NOW()
        WHERE
        usuario_id='$_SESSION[PHD_OPERADOR]'";

$update=mysql_query($query) or die (mysql_error());

$mensaje="<h2 style='color:red; text-align:center'>$Pswd_was_changed</h2>";
$_SESSION['PHD_NIVEL']=4;
require($Include.'clave_chg.inc');


?>
