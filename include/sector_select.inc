<?PHP
/*
    Nombre: sector_select.inc
    Autor: Julio Tuozzo
    Función: Rescata de la base de datos los valores del sector a modificar
    Function: Retrieve of the data base the values of the sector to modify
    Ver: 2.00
*/

## Busco los datos en la base.
// Search in the data base

  $sector_id=$_POST['sector_modificar'];
  $query="SELECT *
          FROM {$MyPHD}sector
          WHERE sector_id='$sector_id'";

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
