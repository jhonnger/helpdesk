<?PHP
/*
    Nombre: novedades_condition.inc
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

## Armo el título con las condiciones de filtro de la consulta
// Compose the title with the query conditions
    
$titulo=$News;

## Armo el query con las condiciones que se pusieron en pantalla.
// Make the query with the conditions


if (strlen($fecha_desde)>0)
        { if (!fecha_valida($fecha_desde))
            {$mensaje.="$fecha_desde, $No_valid_format_date_from <br />";
            }

		  else	
          	{$titulo.=" <b>$From :</b> $fecha_desde,";
		     $fecha_desde=fecha_mysql($fecha_desde);
        	 $condicion_tk.="{$MyPHD}ticket.insert_datetime>'$fecha_desde' AND ";
             $condicion_st.="st.insert_datetime>'$fecha_desde' AND ";
            }
        }

if (strlen($fecha_hasta)>0)
       {if (!fecha_valida($fecha_hasta))
            {$mensaje.="$fecha_hasta, $No_valid_format_date_to <br />";
            }
        else
			{$titulo.=" <b>$To :</b> $fecha_hasta,";

        	 ## Le sumo un día a la fecha hasta para que incluya los tickets ingresados en esa fecha.
          	 $fecha_hasta=date('Y-m-d',strtotime(fecha_mysql($fecha_hasta))+(24*60*60));
             $condicion_tk.="{$MyPHD}ticket.insert_datetime<'$fecha_hasta' AND ";
             $condicion_st.="st.insert_datetime<'$fecha_hasta' AND ";
            }
        }

## Verifico que no haya errores
// Verify that aren't errors

if (strlen($mensaje)>1)
        {$mensaje="<div class='error'>".$mensaje."</div>";
          require('novedades_param.inc');
         exit();
        }


## Armo el WHERE de la consulta
// make the WHERE of the query

$titulo=strlen($titulo)>strlen($News) ? substr($titulo,0,strlen($titulo)-1)."." : "";

$condicion_tk=" WHERE $Filtro_ticket AND ".$condicion_tk;
$condicion_st=" WHERE $Filtro_ticket AND ".$condicion_st;

## Saco el último AND de las cadenas $condicion_tk y $condicion_st y armo la consulta
$condicion_tk=substr($condicion_tk,0,-5);
$condicion_st=substr($condicion_st,0,-5);


$_SESSION['PHD_NEWS_QUERY']="SELECT '$New' AS tipo, seq_ticket_id, insert_datetime, insert_oper, '' AS insert_user, incidente, 
	         '' AS campo_cambiado, '' AS valor_anterior,'' AS valor_actual
			FROM {$MyPHD}ticket
			$condicion_tk
			UNION ALL
			SELECT '$Follow_up' AS tipo, st.seq_ticket_id, st.insert_datetime, st.insert_oper, st.insert_user, comentario AS incidente, 
			campo_cambiado, valor_anterior, valor_actual
			FROM {$MyPHD}sigo_ticket st
			JOIN {$MyPHD}ticket ON {$MyPHD}ticket.seq_ticket_id=st.seq_ticket_id
			$condicion_st";

$_SESSION['PHD_NEWS_TITULO']=$titulo;
    

## cuento cuántos registros arroja la consulta
// Count the rows of the query
    
$query=$_SESSION['PHD_NEWS_QUERY'];
$result=mysql_query($query) or die (mysql_error());
$q_registros = mysql_num_rows($result);
$pagina=1;
$orden="insert_datetime";
$sentido="ASC";
?>
