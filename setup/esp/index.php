<?PHP
/*
    Nombre: index.php
    Autor: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Función: Formulario principal de la configuración de PHD
    Ver: 2.12
*/

if (strlen($_POST[lang])>1)
    { session_start();
      $_SESSION['LANG']=10;
      header("Location: set_lang.php?lang=$_POST[lang]");
    }

if (strlen($_POST[base_dato])>1)
    { session_start();
      $_SESSION['BASE']=10;
      header("Location: set_base.php");
    }

if (strlen($_POST[tables])>1)
    { session_start();
      $_SESSION['TABLES']=10;
      header("Location: set_tables.php");
    }

if (strlen($_POST[mail])>1)
    { session_start();
      $_SESSION['MAIL']=10;
      header("Location: set_mail.php");
    }


if (strlen($_POST[admin])>1)
    { session_start();
      $_SESSION['ADMIN']=10;
      header("Location: set_admin.php");
    }

if (strlen($_POST[atrib])>1)
    { session_start();
      $_SESSION['ATRIB']=10;
      header("Location: set_atrib.php");
    }

if (strlen($_POST[param])>1)
    { session_start();
      $_SESSION['PARAM']=10;
      header("Location: set_param.php");
    }

require('setup_head.inc');
require('make_checks.inc');


if ($c_param=="ok")
     {require('instalado.inc');
      exit();
     }

echo "
<form method='post' name='setup' action='$_SERVER[PHP_SELF]' >

<p class='$c_lang'> Lenguaje de las pantallas. &nbsp; &nbsp;";

     if($c_lang=="now")
        {echo"
         <SELECT name='lang'>
            <OPTION selected value=''> [Seleccione lenguaje] </OPTION> \n
            <OPTION value='ESP'> Español </OPTION> \n
            <OPTION value='ENG'> Inglés </OPTION> \n
        </SELECT> &nbsp; &nbsp;
        <input class='boton_bold' type='submit' value='Configurar'>
        ";
        }
    elseif ($c_lang=="ok")
        {echo "<b>OK.</b>";

        }

echo   "</p>

      <p class='$c_base_dato'>
      Par&aacute;metros de acceso a la base de datos. &nbsp; &nbsp;";

     if($c_base_dato=="now")
        {echo"<input class='boton_bold' type='submit' value='Configurar' name='base_dato'>
        ";
        }
    elseif ($c_base_dato=="ok")
        {echo "<b>OK.</b>";

        }

echo      "</p>


      <p class='$c_create'>
      Creaci&oacute;n de las tablas en la base de datos. &nbsp; &nbsp;";

      if ($c_create=="now")
         {echo "<input class='boton_bold' type='submit' value='Crear tablas' name='tables'>";
         }
      elseif ($c_create=="ok")
         {echo "<b>OK.</b>";
         }

echo "  </p>


      <P class='$c_mail'>
      Par&aacute;metros para enviar correo electr&oacute;nico. &nbsp; &nbsp;";

 if ($c_mail=="now")
         {echo "<input class='boton_bold' type='submit' value='Configurar' name='mail'>";
         }
      elseif ($c_mail=="ok")
         {echo "<b>OK.</b>";
         }


echo "  </p>


      <P class='$c_admin'>
      Alta de operador con permiso de administrador. &nbsp; &nbsp;";

 if ($c_admin=="now")
         {echo "<input class='boton_bold' type='submit' value='Crear administrador' name='admin'>";
         }
      elseif ($c_admin=="ok")
         {echo "<b>OK.</b>";
         }


echo " </p>

      <P class='$c_atrib'>
      Atributos del Ticket. &nbsp; &nbsp;";

if ($c_atrib=="now")
         {echo "<input class='boton_bold' type='submit' value='Crear atributos' name='atrib'>";
         }

      elseif ($c_atrib=="ok")
         {echo "<b>OK.</b>";
         }

echo   "</p>

      <p class='$c_param'>
      Par&aacute;metros generales. &nbsp; &nbsp;";
      if ($c_param=="now")
         {echo "<input class='boton_bold' type='submit' value='Configurar' name='param'>";
         }

echo "</p>

   </form>
  </body>
</html>";

?>

