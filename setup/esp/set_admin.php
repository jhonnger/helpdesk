<?PHP
/*
    Nombre: set_admin.php
    Autor: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Función: Da de alta el operador con permisos de administrador en la base
    Ver: 2.12
*/

session_start();
require('../../config.inc.php');

if (!isset($_SESSION['ADMIN']))

    {include('setup_head.inc');
     echo "<p class='danger'>LLAMADA INVALIDA</p>";
     exit();
    }



if (!isset($_POST[b_admin]))
    {require('set_admin.inc');
     exit();
    }

## Preparo los datos ingresados
$operador=trim(strip_tags($_POST['operador']));
$ape_y_nom=trim(strip_tags($_POST['ape_y_nom']));
$e_mail=trim(strip_tags($_POST['e_mail']));
$contrasenia=strip_tags($_POST['contrasenia']);
$reingresa=strip_tags($_POST['reingresa']);
$sector_id=trim(strip_tags($_POST['sector_id']));
$sector_nombre=trim(strip_tags($_POST['sector_nombre']));

## Valido que el operador tenga por lo menos tres dígitos.

if (strlen($operador)<1)
    {$mensaje="<p class='danger'> ERROR - El operador no puede estar en blanco.</p>";
     include('set_admin.inc');
     exit();
    }

## Valido que el apellido y nombre no venga en blanco.

if (strlen($ape_y_nom)<1)
    {$mensaje="<p class='danger'> ERROR - El Apellido y nombre no puede estar en blanco.</p>";
     include('set_admin.inc');
     exit();
    }


## Valido que sean letras y/o números

if(!preg_match('#^[a-zA-Z0-9]+$#', $contrasenia))

   {$mensaje="<p class='danger'> ERROR - La contrase&ntilde;a debe estar compuesta solo por letras y/o n&uacute;meros.</p>";
     include('set_admin.inc');
     exit();

    }

## Valido que la contraseña y su reingreso sean iguales

if ($contrasenia!= $reingresa)
    {$mensaje="<p class='danger'> ERROR - La contrase&ntilde;a y su reingreso son distintos</p>";
     include('set_admin.inc');
     exit();
    }


## Verifico que la nueva contraseña no tenga más de tres letras/números repetidos

foreach (count_chars($contrasenia, 1) as $cantidad)
    {if ($cantidad>3)
        {$mensaje="<p class='danger'> ERROR - La contrase&ntilde;a tiene demasiados d&iacute;gitos repetidos.</p>";
         include('set_admin.inc');
         exit();
        }
    }


## Valido que por lo menos tenga seis dígitos


if (strlen($contrasenia)<6)
   {$mensaje="<p class='danger'> ERROR - La contrase&ntilde;a debe tener por lo menos seis d&iacute;gitos.</p>";
     include('set_admin.inc');
     exit();

    }

## Valido que el operador y la contraseña sean distintos


if (strtoupper($contrasenia)==$operador)
   {$mensaje="<p class='danger'> ERROR - La contrase&ntilde;a y el c&oacute;digo de operador deben ser distintos.</p>";
     include('set_admin.inc');
     exit();

    }


## Valido el formato de correo electrónico

if (!preg_match('#^.+@.+\\..+$#',$e_mail))
    {$mensaje="<p class='danger'> ERROR - Formato de correo electr&oacute;nico no v&aacute;lido.</p>";
     include('set_admin.inc');
     exit();
    }

## Valido que el código del área no venga en blanco.

if (strlen($sector_id)<1)
    {$mensaje="<p class='danger'> ERROR - El c&oacute;digo del &aacute;rea no puede estar en blanco.</p>";
     include('set_admin.inc');
     exit();
    }

## Valido que el apellido y nombre no venga en blanco.

if (strlen($sector_nombre)<1)
    {$mensaje="<p class='danger'> ERROR - El nombre del &aacute;rea no puede estar en blanco.</p>";
     include('set_admin.inc');
     exit();
    }


## Me conecto con la base de datos

if(!mysql_connect($Host,$Usuario,$Contrasena) or !mysql_select_db($Base))
    {$mensaje="<p class='danger'>ERROR - No se estableci&oacute; la conexi&oacute;n con la base de datos.</p>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_admin.inc');
     exit();
    }

## Inserto el operador administrador
$contrasenia=md5($contrasenia);
$query="INSERT INTO operador VALUES
        ('$operador',
         '$ape_y_nom',
         '$sector_id',
         '$e_mail',
         '$contrasenia',
         'S',
         20,
         DATE_ADD(NOW(),INTERVAL 30 DAY),
         'N',
         'N',
         'SETUP',
         NOW(),
         'SETUP',
         NOW())";

if (!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de insert de datos en tabla operador</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_admin.inc');
     exit();

    }

## Inserto el área del administrador

$query="INSERT INTO sector VALUES
        ('$sector_id',
         '$sector_nombre',
         'S',
         'SETUP',
         NOW(),
         'SETUP',
         NOW())";

if (!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de insert de datos en tabla sector</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_admin.inc');
     exit();

    }



session_destroy();
header("Location: index.php");
?>
