<?PHP
/*
    Nombre: consulta_condition.inc
    Autor: Julio Tuozzo
    Función: Arma la condición de la consulta
    Function: Make the query condition
    Ver: 2.12
*/

## Verifico si esta seteado el botón de submit "buscar", si es así
## armo la condición de búsqueda y la guardo en una variable global,
## calculo el número de páginas para paginar el resultado.
## De lo contrario rescato la condición desde la variable global y veo
## en qué página tengo que buscar.

// Verify if ius set button of submit “buscar”, if he is thus make the condition
// search and keep it in a global variable, calculate the number of pages to paging
// the result. Otherwise retrieve the condition from the global variable and get in
// what page must look for.

## inicializo las variables
// inicializig variables
unset($_SESSION['PHD_MAIN_CONS']);
$mensaje="";


if (get_magic_quotes_gpc())
    { foreach($_POST as $clave => $valor)
      {$_POST[$clave]=stripslashes($_POST[$clave]);
      }
    }

foreach($_POST as $clave => $valor)
     {$campo=$clave;
      $$campo=trim(htmlentities($valor,ENT_QUOTES,"ISO-8859-1"));
     }
$_SESSION['PHD_INCIDENTE']=$incidente;
$_SESSION['PHD_COMENTARIO_Q']=$comentario;

## Armo el título con las condiciones de filtro de la consulta
// Compose the title with the query conditions
    
$titulo=$Query_head;

## Armo el query con las condiciones que se pusieron en pantalla.
// Make the query with the conditions


if (strlen($ticket)>0)
        {$condicion.="seq_ticket_id='$ticket' AND ";
         $titulo.=" <b>$Ticket:</b> # $ticket,";
        }

if (strlen($fecha_desde)>0)
        { if (!fecha_valida($fecha_desde))
            {$mensaje.="$fecha_desde, $No_valid_format_date_from <br />";
            }
          $titulo.=" <b>$From $Date:</b> $fecha_desde,";
          $fecha_desde=fecha_mysql($fecha_desde);
          $condicion.="fecha>'$fecha_desde' AND ";
        }

if (strlen($fecha_hasta)>0)
       {if (!fecha_valida($fecha_hasta))
            {$mensaje.="$fecha_hasta, $No_valid_format_date_to <br />";
            }
          $titulo.=" <b>$To $Date:</b> $fecha_hasta,";

        ## Le sumo un día a la fecha hasta para que incluya los tickets ingresados en esa fecha.
        //
          $fecha_hasta=date('Y-m-d',strtotime(fecha_mysql($fecha_hasta))+(24*60*60));
          $condicion.="fecha<'$fecha_hasta' AND ";
        }

if (strlen($operador)>0)
        {$condicion.="operador_id='$operador' AND ";
         $titulo.=" <b>$Operator:</b> $operador,";
        }

if (strlen($operador_sector_id)>0)
        {$condicion.="operador_sector_id='$operador_sector_id' AND ";
         $titulo.=" <b>$Sector $Operator:</b> $operador_sector_id,";
        }

if (strlen($contacto)>0)
        {$condicion.="contacto='$contacto' AND ";
         $titulo.=" <b>$Contact:</b> $contacto,";
        }

if (strlen($usuario)>0)
        {$condicion.="usuario_id='$usuario' AND ";
         $titulo.=" <b>$User:</b> $usuario,";
        }

if (strlen($area_id)>0)
        {$condicion.="area_id='$area_id' AND ";
         $titulo.=" <b>$Area:</b> $area_id,";
        }

if (strlen($asignado_a)>0)
        {$condicion.="asignado_a='$asignado_a' AND ";
         $titulo.=" <b>$Assigned_to:</b> $asignado_a,";
        }

if (strlen($asignado_a_sector)>0)
        {$condicion.="asignado_a_sector='$asignado_a_sector' AND ";
         $titulo.=" <b>$Assigned_to $Sector:</b> $asignado_a_sector,";
        }

if (strlen($prioridad)>0)
       {$condicion.="prioridad='$prioridad' AND ";
         $titulo.=" <b>$Priority:</b> $prioridad,";
        }

if (strlen($incidente)>0)
        {$condicion.="incidente LIKE '%$incidente%' AND ";
        }

if (strlen($proceso)>0)
        {$condicion.="proceso='$proceso' AND ";
         $titulo.=" <b>$Process:</b> $proceso,";
        }

if (strlen($tipo)>0)
        {$condicion.="tipo='$tipo' AND ";
         $titulo.=" <b>$Type:</b> $tipo,";
        }

if (strlen($sub_tipo)>0)
        {$condicion.="sub_tipo='$sub_tipo' AND ";
         $titulo.=" <b>$Subtype:</b> $sub_tipo,";
        }


if (strlen($estado)>0)
        {$condicion.="estado='$estado' AND ";
         $titulo.=" <b>$State:</b> $estado,";
        }


if (strlen($fecha_ue_desde)>0)
        { if (!fecha_valida($fecha_ue_desde))
            {$mensaje.="$fecha_ue_desde, $No_valid_format_lsd_from <br />";
            }
          $titulo.=" <b>$Last_state_date $From:</b> $fecha_ue_desde,";
          $fecha_ue_desde=fecha_mysql($fecha_ue_desde);
          $condicion.="fecha_ultimo_estado>'$fecha_ue_desde' AND ";
        }

if (strlen($fecha_ue_hasta)>0)
       {if (!fecha_valida($fecha_ue_hasta))
            {$mensaje.="$fecha_ue_hasta, $No_valid_format_lsd_to <br />";
            }
          $titulo.=" <b>$Last_state_date $To:</b> $fecha_ue_hasta,";

        ## Le sumo un día a la fecha último estado hasta para que incluya los tickets de esa fecha .
          $fecha_ue_hasta=date('Y-m-d',strtotime(fecha_mysql($fecha_ue_hasta))+(24*60*60));
          $condicion.="fecha_ultimo_estado<'$fecha_ue_hasta' AND ";
        }

if (strlen($comentario)>0)
        {$condicion.="seq_ticket_id IN (select seq_ticket_id FROM {$MyPHD}sigo_ticket WHERE comentario LIKE '%$comentario%') AND ";
        }

## Verifico que no haya errores
// Verify that aren't errors

if (strlen($mensaje)>1)
        {$mensaje="<div class='error'>".$mensaje."</div>";
          require('consulta_param.inc');
         exit();
        }


## Armo el WHERE de la consulta
// make the WHERE of the query

$condicion=" WHERE $Filtro_ticket AND ".$condicion;
$titulo=strlen($titulo)>strlen($Query_head) ? substr($titulo,0,strlen($titulo)-1)."." : "";
## Saco el último AND de la cadena $condicion y armo la consulta
$_SESSION['PHD_CONDICION']=$condicion=substr($condicion,0,(strlen($condicion)-5));
$_SESSION['PHD_TITULO']=$titulo;
    

## cuento cuántos registros arroja la consulta
// Count the rows of the query
    
$query="SELECT COUNT(*) AS cuantos
            FROM {$MyPHD}ticket $condicion";
$result=mysql_query($query) or die (mysql_error().$query);
$row = mysql_fetch_array($result);
$q_registros=$row['cuantos'];
$pagina=1;
$orden="seq_ticket_id";
$sentido="ASC";
?>
