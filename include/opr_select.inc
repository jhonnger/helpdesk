<?PHP
/*
    Nombre: opr_select.inc
    Autor: Julio Tuozzo
    Función: Rescata de la base de datos los valores del operador a modificar
    Function: It retrieve of the data base the values of the operator to modify
    Ver: 2.00
*/

## Busco los datos en la base.
// Search in the data base

  $operador=$_POST['modificar'];
  $query="SELECT *
          FROM {$MyPHD}operador
          WHERE operador_id='$operador'";

  $result=mysql_query($query) or die (mysql_error());
  $row = mysql_fetch_array($result);

## Le doy forma al vector de los datos
// Formating the data vector.

     foreach($row as $clave => $valor)
      {$row[$clave]=htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1");
      }

### inicializo las variables

    $ape_y_nom=$row['ape_y_nom'];
    $nivel=$row['nivel'];
    $e_mail=$row['e_mail'];
    $sector_id=$row['sector_id'];

    $aux_select="_$nivel";
    $$aux_select="selected";

    if ($row['privado']=="S")
        {$privado="S";
         $private_check="checked";
        }
    else
        {$privado="N";
         $private_check="";
        }

    if ($row['avisar_asignado']=="S")
        {$avisar_asignado="S";
         $avisar_asignado_check="checked";
        }
    else
        {$avisar_asignado="N";
         $avisar_asignado_check="";
        }

    if ($row['avisar_solicitud']=="S")
        {$avisar_solicitud="S";
         $avisar_solicitud_check="checked";
        }
    else
        {$avisar_solicitud="N";
         $avisar_solicitud_check="";
        }

?>
