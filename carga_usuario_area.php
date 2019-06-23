<?PHP
/*
    Nombre: carga_usuario_area.php
    Autor: Julio Tuozzo 
    Función: Controlador de subida de archivo con usuarios y areas
    Ver: 2.12
*/


session_start();
require('config.inc.php');
include($Include.'lang.inc');
if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<20)
    {include($Include.'login.inc');
     exit();
    }

require('funciones.inc.php');
$text_max_attach=conv_bytes($_SESSION['PHD_MAX_ATTACH']);

## Me conecto con la base de datos
// Database connect

$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

if (get_magic_quotes_gpc())
    { foreach($_POST as $clave => $valor)
      {$_POST[$clave]=stripslashes($_POST[$clave]);
      }
    }

foreach($_POST as $clave => $valor)
     {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
     }

if (get_magic_quotes_gpc())
    { foreach($_GET as $clave => $valor)
      {$_GET[$clave]=stripslashes($_GET[$clave]);
      }
    }

foreach($_GET as $clave => $valor)
     {$_GET[$clave]=trim(htmlentities($_GET[$clave],ENT_QUOTES,"ISO-8859-1"));
     }


if (isset($_POST['inicio']))
    {header("Location: index.php");
     exit();
    }

if (isset($_POST['cargar']))
		{require($Include.'carga_usuario_area_load.inc');
		}

if (isset($_POST['procesar']))
		{require($Include.'carga_usuario_area_proc.inc');
		}
	
if (isset($_POST['eliminar']))
		{$query="DELETE FROM {$MyPHD}usuario_area_tmp";
		 $result=mysql_query($query) or die (mysql_error());
		 unset($_GET);
		}
if (!isset($_GET['pagina']))
		{// Verifico si ya hay registros ingresados en el temporal

		 $query="SELECT count(*) as cuantos FROM {$MyPHD}usuario_area_tmp";
		 $result=mysql_query($query) or die (mysql_error());

		 $row = mysql_fetch_array($result);
		 $q_registros=$row['cuantos'];
	     $pagina=1;
    	 $orden="usuario_id";
    	 $sentido="ASC";
		}
else
	    {$q_registros=$_GET['q_registros'];
    	 $pagina=$_GET['pagina'];
	     $orden=$_GET['orden'];
    	 $sentido=$_GET['sentido'];
    	}

## Calculo desde que registro muestro en función de la página
// Calculate since registry show based on the page.

$desde_reg=($pagina-1)*$_SESSION['PHD_MAX_LINES_SCREEN'];

if($sentido=="DESC")
        {$_aux_var="arr_$orden";
         $$_aux_var="&nbsp; &#9660;";
         $_aux_var="sen_$orden";
         $$_aux_var="ASC";
        }
else
        {$_aux_var="arr_$orden";
         $$_aux_var="&nbsp; &#9650;";
         $_aux_var="sen_$orden";
         $$_aux_var="DESC";
        }

if($q_registros>0)
	{$query="SELECT * FROM {$MyPHD}usuario_area_tmp ORDER BY $orden $sentido LIMIT $desde_reg, {$_SESSION['PHD_MAX_LINES_SCREEN']}";

	 $result=mysql_query($query) or die (mysql_error());

	 require($Include.'carga_usuario_area_list.inc');
	}
else
	{require($Include.'carga_usuario_area.inc');
	}
?>
