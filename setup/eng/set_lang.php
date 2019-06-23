<?PHP
/*
    Nombre: set_lang.php
    Autor: Julio Tuozzo
    Función: Configura el lenguaje de la aplicación.
    Ver: 2.00
*/
session_start();
if (!isset($_SESSION['LANG']) or ($_GET[lang]!='ESP' and $_GET[lang]!='ENG'))

    {include('setup_head.inc');
     echo "<p class='danger'>INVALID CALL</p>";
     exit();
    }
session_destroy();

$path_lang="../../include/";

    switch ($_GET[lang])
    {case "ESP":
     if (!is_readable($path_lang."lang_esp.inc"))
        {include('setup_head.inc');
          echo "<p class='danger'><b>IMPOSSIBLE TO READ FILE lang_esp.inc </b></p>
     <p class='ok'>Verify if the file exists and the access permission and try again.<br />
     The lang_esp.inc file is placed in <b>/phd_2_00/include/.</b></p>";
         exit();
        }
     break;
     case "ENG":
     if (!is_readable($path_lang."lang_eng.inc"))
        {include('setup_head.inc');
          echo "<p class='danger'><b>IMPOSSIBLE TO READ FILE  lang_eng.inc </b></p>
     <p class='ok'>Verify if the file exists and the access permission and try again.<br />
     The lang_eng.inc file is placed in <b>/phd_2_00/include/.</b></p>";
         exit();
         }

     break;
    }

if (!is_writable($path_lang."lang.inc"))
    {include('setup_head.inc');
     echo "<p class='danger'><b>IMPOSSIBLE TO WRITE FILE lang.inc </b></p>
     <p class='ok'>Verify if the file exists and the access permission and try again.<br />
     The lang.inc file is placed in <b>/phd_2_00/include/.</b>
     </p>";
     exit();
    }

if (!unlink($path_lang."lang.inc"))
    {include('setup_head.inc');
     echo "<p class='danger'><b>IMPOSSIBLE TO DELETE FILE  lang.inc </b></p>
     <p class='ok'>Verify if the file exists and the access permission and try again.<br />
     The lang.inc file is placed in <b>/phd_2_00/include/.</b>
     </p>";
     exit();
    }

    switch ($_GET[lang])
    {case "ESP":

     if (!copy($path_lang."lang_esp.inc",$path_lang."lang.inc"))
        {include('setup_head.inc');
          echo "<p class='danger'><b>IMPOSSIBLE TO COPY FILE  lang_esp.inc </b></p>
        <p class='ok'>Verify if the file exists and the access permission and try again.</p>";
        exit();
        }
     break;
     case "ENG":

     if (!copy($path_lang."lang_eng.inc",$path_lang."lang.inc"))
        {include('setup_head.inc');
          echo "<p class='danger'><b>IMPOSSIBLE TO COPY FILE  lang_eng.inc </b></p>
         <p class='ok'>Verify if the file exists and the access permission and try again.</p>";
        exit();
        }
     break;
    }

header("Location: index.php");
?>
