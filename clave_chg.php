<?PHP
/*
    Nombre: clave_chg.php
    Autor: Julio Tuozzo
    Funci�n: Cambio de clave.
    Funcition: change password.
    Ver: 2.12
*/

## Verifico que se encuentre validado el operador, si no es asi lo
## dirijo a la pantalla de login.
// Verify that one is validated the operator, if it is not therefore
// redirect to the screen of login.

session_start();
require('config.inc.php');
require($Include.'lang.inc');
require($Include.'lang-script.inc');
if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<5)
    {require($Include.'login.inc');
     exit();
    }

## Verifico si entr� por expiraci�n de contrase�a para colocar
## el mensaje correspondiente
// Verify if the password was expired to place the corresponding message.

elseif ($_SESSION['PHD_NIVEL']<10)
   {$mensaje=$Pswd_expired;
    }

## Verifico que no haya cancelado, si es as� vuelve al index
// Check that it has not cancelled, if it is thus returns to index.

if (isset($_POST['salir']))
    {header("Location: index.php");
    }

## Verfico que se haya ingresado por "submit"", si es as� resto
## uno a la cantidad de intentos, si es menor a tres mato la sesi�n
## y voy a la pantalla de login, si no es as�
## coloco la pantalla que pide el cambio de clave e inicializo
## la variable que cuenta los intentos de cambio.
// Verfy that has entered by �submit "", if  one to the amount on attempts
// is thus rest, if is lower to three, kills the session and goes to the screen
// of login, if he is not thus change to the screen that requests the change of
// key and initialize the variable that counts the attempts of change.

if(isSet($_POST['cambiar']))
    {$_SESSION['PHD_INTENTOS']=$_SESSION['PHD_INTENTOS']-1;
     if ($_SESSION['PHD_INTENTOS']<0)
        {session_destroy();
         header("Location: index.php");
        }
    }
else
	{$_SESSION['PHD_INTENTOS']=3;
     require($Include.'clave_chg.inc');
	 exit();
	}

## Me conecto con la base de datos.
// Connect to the database.

$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());



## Valido que la nueva contrase�a y su reingreso sean iguales
// Check that the new password and re type are equal

if ($_POST[nueva]!= $_POST[reingresa])
    {$mensaje=$Pswd_not_equal;
     require($Include.'clave_chg.inc');
     exit();
    }

## asigno la nueva contrase�a y valido que sean letras y/o n�meros
// Assign the new password and check that is letters and/or numbers

$nueva=$_POST[nueva];

if(!preg_match('#^[a-zA-Z0-9]+$#', $nueva))

   {$mensaje=$Pswd_only_ln;
     require($Include.'clave_chg.inc');
     exit();

    }


## Verifico que la nueva contrase�a no tenga m�s de tres letras/n�meros repetidos
// Chack that the new password does not have more than three repeated letters/numbers

foreach (count_chars($nueva, 1) as $cantidad)
    {if ($cantidad>3)
        {$mensaje=$Pswd_repeat_d;
         require($Include.'clave_chg.inc');
         exit();
        }
    }


## Valido que por lo menos tenga seis d�gitos
## Check that at least has six digits

if (strlen($nueva)<6)
   {$mensaje=$Pswd_six_d;
     require($Include.'clave_chg.inc');
     exit();

    }

## Valido que el operador y la contrase�a sean distintos
// Check that the operator and the password are different

if ($nueva==$_SESSION[PHD_OPERADOR])
   {$mensaje=$Pswd_same_user;
     require($Include.'clave_chg.inc');
     exit();

    }


## Verifico la contrase�a anterior
// verify the previous password

$md5_actual=md5($_POST['actual']);

$query="SELECT * FROM {$MyPHD}operador WHERE operador_id='$_SESSION[PHD_OPERADOR]' AND contrasenia='$md5_actual'";
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

## Verifico que la nueva contrase�a no se haya utilizado en los �ltimos $_SESSION[PHD_DIAS_PSW] d�as
// Verify that the new password has not been used in the last $_SESSION[PHD_DIAS_PSW] days

$md5_nueva=md5($nueva);

$query="SELECT * FROM {$MyPHD}hist_pass
        WHERE operador_id='$_SESSION[PHD_OPERADOR]' AND
        contrasenia='$md5_nueva' AND
        insert_datetime>DATE_SUB(NOW(), INTERVAL $_SESSION[PHD_DIAS_PSW] DAY)";

$select=mysql_query($query);
$q_filas = mysql_num_rows($select);

if ($q_filas>0)
    {$mensaje=$Pswd_used;
     require($Include.'clave_chg.inc');
     exit();
    }

## Todo OK, actualizo la nueva contrase�a
// All OK, update the new password.

$query="UPDATE {$MyPHD}operador SET
        contrasenia='$md5_nueva',
        expira_clave=DATE_ADD(NOW(),INTERVAL $_SESSION[PHD_VALIDEZ_PSW] DAY),
        update_oper='$_SESSION[PHD_OPERADOR]',
        update_datetime=NOW()
        WHERE
        operador_id='$_SESSION[PHD_OPERADOR]'";

$update=mysql_query($query) or die (mysql_error());

## Guardo la nueva contrase�a en el hist�rico
// Save the new password in the historical file

$query="INSERT INTO {$MyPHD}hist_pass VALUES
        ('$_SESSION[PHD_OPERADOR]',
         '$md5_actual',
         '$_SESSION[PHD_OPERADOR]',
          NOW())";

$insert=mysql_query($query) or die (mysql_error());


## Finalmente, si corresponde, restauro el nivel de ejecuci�n que ten�a
// Finally, if it corresponds, recover the execution level that it had

    if (isSet($_SESSION['PHD_CLAVE_CHG']))
        {$_SESSION['PHD_NIVEL']=$_SESSION['PHD_CLAVE_CHG'];
        }
$mensaje="<script language='javascript'>window.alert('$_Pswd_was_changed') ; window.location='index.php'</script>";
require($Include.'clave_chg.inc');

?>
