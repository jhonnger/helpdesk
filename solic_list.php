<?PHP
/*
    Nombre: solic_list.php
    Autor: Julio Tuozzo
    Función: Lista de solicitudes
    Function: user's request list
    Ver: 2.12

*/

session_start();
require('config.inc.php');
require($Include.'lang.inc');
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

if($_GET['op']=="user")
      {if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']!=4)
                {require($Include.'user_login.inc');
                 exit();
                }
       else
                {$op_user="&op=user";
                 $condicion="usuario_id='{$_SESSION['PHD_OPERADOR']}' AND ";
                 $menu="user_menu.inc";
                 $sentido_inicial="DESC";
                 $opcion="<h2>$See_my_request</h2>";
                }
      }
elseif (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<10)
    {include($Include.'login.inc');
     exit();
    }
else
    {$menu="menu.inc";
     $filtro_pendientes="estado='PEN' AND not exists (select 1 from {$MyPHD}ticket where {$MyPHD}ticket.seq_ticket_id = {$MyPHD}solicitud.seq_ticket_id) AND ";
     $sentido_inicial="ASC";
     $estado_inicial="PEN";
     $opcion="$Support_request";
    }


## Me conecto con la base de datos
// Connect with the database

    $Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
    $Uso=mysql_select_db($Base) or die (mysql_error());

$mensaje="";

## Si es la primer llamada a la página muestro por default las solicitudes
## pendientes.
// if is the first call to the page I show by default the pending requests.

if (!isset($_POST[buscar]) and !isset($_GET[pagina]))
    {$condicion=" $filtro_pendientes $condicion";
     $_SESSION['PHD_SOLIC_COND']=$condicion=substr($condicion,0,(strlen($condicion)-5));
     $query="SELECT COUNT(*) AS cuantos
             FROM {$MyPHD}solicitud where $condicion";
     ## Saco el último AND de la cadena $condicion y armo la consulta

     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);
     $q_registros=$row['cuantos'];
     $pagina=1;
     $orden="seq_solicitud_id";

     unset($_SESSION[PHD_SOL_FECHA_DESDE]);
     unset($_SESSION[PHD_SOL_FECHA_HASTA]);
     unset($_SESSION[PHD_SEQ_SOLICITUD_ID]);
     $_SESSION[PHD_SOL_ESTADO]=$estado_inicial;

     header("Location: $_SERVER[PHP_SELF]?pagina=$pagina&q_registros=$q_registros&orden=$orden&sentido=$sentido_inicial$op_user");
    }

## Verifico si esta seteado el botón de submit "buscar", si es así
## armo la condición de búsqueda y la guardo en una variable global,
## calculo el número de páginas para paginar el resultado.
## De lo contrario rescato la condición desde la variable global y veo
## en qué página tengo que buscar.

// Verify if ius set button of submit “buscar”, if he is thus make the condition
// search and keep it in a global variable, calculate the number of pages to paging
// the result. Otherwise retrieve the condition from the global variable and get in
// what page must look for.

if (isset($_POST[buscar]))

    {## inicializo las variables
     // inicializig variables

    $_SESSION[PHD_SOL_FECHA_DESDE]=$fecha_desde=trim($_POST[fecha_desde]);
    $_SESSION[PHD_SOL_FECHA_HASTA]=$fecha_hasta=trim($_POST[fecha_hasta]);
    $_SESSION[PHD_SOL_ESTADO]=$estado=trim($_POST[estado]);
    $_SESSION[PHD_SEQ_SOLICITUD_ID]=$seq_solicitud_id=trim($_POST[seq_solicitud_id]);


    ## Armo el query con las condiciones que se pusieron en pantalla.
    // Make the query with the conditions



    if (strlen($seq_solicitud_id)>0)
        {$condicion.="seq_solicitud_id=$seq_solicitud_id AND ";
        }


    if (strlen($fecha_desde)>0)
        { if (!fecha_valida($fecha_desde))
              {$mensaje.="$fecha_desde, $No_valid_format_date_from <br />";
               $condicion.="fecha>DATE_ADD(NOW(),INTERVAL 30 DAY) AND ";
              }
          else
              {$aux_fecha_desde=fecha_mysql($fecha_desde);
               $condicion.="fecha>'$aux_fecha_desde' AND ";
              }
        }

    if (strlen($fecha_hasta)>0)
       {if (!fecha_valida($fecha_hasta))
            {$mensaje.="$fecha_hasta, $No_valid_format_date_to";
             $condicion.="fecha>DATE_ADD(NOW(),INTERVAL 30 DAY) AND ";
            }
        else
            {## Le sumo un día a la fecha hasta para que incluya las solicitudes ingresadas en esa fecha.
             $aux_fecha_hasta=date('Y-m-d',strtotime(fecha_mysql($fecha_hasta))+(24*60*60));
             $condicion.="fecha<'$aux_fecha_hasta' AND ";
            }
        }

    if (strlen($estado)>0)
        {
        	if($estado != 'PEN')
        		{
        			$condicion.="estado='$estado' AND ";
        		}
        		else
        		{
        			$condicion.="estado='$estado' AND ";
        			$condicion.="not exists (select 1 from {$MyPHD}ticket ";
        			$condicion.="where {$MyPHD}ticket.seq_ticket_id =";
        			$condicion.=" {$MyPHD}solicitud.seq_ticket_id) AND ";
        		}
        }



    ## Armo el WHERE de la consulta
    // make the WHERE of the query

    if(isset($condicion))
        {  $condicion="  	 ".$condicion;
           ## Saco el último AND de la cadena $condicion y armo la consulta
           $_SESSION['PHD_SOLIC_COND']=$condicion=substr($condicion,0,(strlen($condicion)-5));

        }
    else
        {unset($_SESSION['PHD_SOLIC_COND']);
        }


    ## cuento cuántos registros arroja la consulta
    // Count the rows of the query
    

    $query="SELECT COUNT(*) AS cuantos
            FROM {$MyPHD}solicitud where $condicion";

    $result=mysql_query($query) or die (mysql_error());
    $row = mysql_fetch_array($result);
    $q_registros=$row['cuantos'];
    $pagina=1;
    $orden="seq_solicitud_id";
    $sentido="ASC";
    }
else
    {$condicion=$_SESSION['PHD_SOLIC_COND'];
     $q_registros=$_GET[q_registros];
     $pagina=$_GET[pagina];
     $orden=$_GET[orden];
     $sentido=$_GET[sentido];
    }

include($Include.'solic_list.inc');

?>

