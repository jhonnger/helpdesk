<?PHP
/*
    Nombre: area_select.inc
    Autor: Julio Tuozzo
    Función: Rescata de la base de datos los valores del área a modificar
    Function: Retrieve of the data base the values of the area to modify
    Ver: 2.00
*/

## Busco los datos en la base.
// Search in the data base

  $area_id=$_POST['area_modificar'];
  $query="SELECT *
          FROM {$MyPHD}area
          WHERE area_id='$area_id'";

  $result=mysql_query($query) or die (mysql_error());
  $row = mysql_fetch_array($result);

### inicializo las variables

foreach($row as $clave => $valor)
      {$row[$clave]=trim(htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1"));
      }

    $nombre=$row['nombre'];

    if ($row['activo']=="S")
        {$activo="S";
         $active_check="checked";
        }
    else
        {$activo="N";
         $active_check="";
        }

?>
