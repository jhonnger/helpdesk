<?PHP
/*
    Nombre: set_lang.php
    Autor: Julio Tuozzo
    Función: Configura el lenguaje de la aplicación.
    Ver: 2.12
*/
session_start();
if (!isset($_SESSION['LANG']) or ($_GET[lang]!='ESP' and $_GET[lang]!='ENG'))

    {include('setup_head.inc');
     echo "<p class='danger'>LLAMADA INVALIDA</p>";
     exit();
    }
session_destroy();
$path_lang="../../include/";

    switch ($_GET[lang])
    {case "ESP":
     if (!is_readable($path_lang."lang_esp.inc"))
        {include('setup_head.inc');
          echo "<p class='danger'><b>IMPOSIBLE LEER ARCHIVO lang_esp.inc </b></p>
     <p class='ok'>Verifique que el archivo exista y los permisos que tiene, e intente nuevamente.<br />
     El archivo lang_esp.inc se encuentra inicialmente en <b>/phd_2_12/include/.</b></p>";
         exit();
        }
     break;
     case "ENG":
     if (!is_readable($path_lang."lang_eng.inc"))
        {include('setup_head.inc');
          echo "<p class='danger'><b>IMPOSIBLE LEER ARCHIVO  lang_eng.inc </b></p>
     <p class='ok'>Verifique que el archivo exista y los permisos que tiene, e intente nuevamente.<br />
     El archivo lang_eng.inc se encuentra inicialmente en <b>/phd_2_12/include/.</b></p>";
         exit();
         }

     break;
    }

if (!is_writable($path_lang."lang.inc"))
    {include('setup_head.inc');
     echo "<p class='danger'><b>IMPOSIBLE ESCRIBIR ARCHIVO  lang.inc </b></p>
     <p class='ok'>Verifique que exista y que tenga permiso de escritura, e intente nuevamente.<br />
     El archivo lang.inc se encuentra inicialmente en <b>/phd_2_12/include/.</b>
     </p>";
     exit();
    }

if (!unlink($path_lang."lang.inc"))
    {include('setup_head.inc');
     echo "<p class='danger'><b>IMPOSIBLE BORRAR ARCHIVO lang.inc </b></p>
     <p class='ok'>Verifique que exista y que tenga permiso de escritura, e intente nuevamente.<br />
     El archivo lang.inc se encuentra inicialmente en <b>/phd_2_12/include/.</b>
     </p>";
     exit();
    }

    switch ($_GET[lang])
    {case "ESP":

     if (!copy($path_lang."lang_esp.inc",$path_lang."lang.inc"))
        {include('setup_head.inc');
          echo "<p class='danger'><b>IMPOSIBLE COPIAR ARCHIVO lang_esp.inc </b></p>
        <p class='ok'>Verifique los permisos sobre ese archivo, debe tener permiso de lectura, e intente nuevamente.</p>";
        exit();
        }
     break;
     case "ENG":

     if (!copy($path_lang."lang_eng.inc",$path_lang."lang.inc"))
        {include('setup_head.inc');
          echo "<p class='danger'><b>IMPOSIBLE COPIAR ARCHIVO lang_eng.inc </b></p>
         <p class='ok'>Verifique los permisos sobre ese archivo, debe tener permiso de lectura, e intente nuevamente.</p>";
        exit();
        }
     break;
    }

header("Location: index.php");
?>
