<?PHP
/*
    Nombre: user_select.inc
    Autor: Julio Tuozzo
    Función: Rescata de la base de datos los valores del usuario a modificar
    Function: It retrieve of the data base the values of the user to modify
    Ver: 2.00
*/

## Busco los datos en la base.
// Search in the data base

  $usuario_id=$_POST['usr_modificar'];
  $query="SELECT *
          FROM {$MyPHD}usuario
          WHERE usuario_id='$usuario_id'";

  $result=mysql_query($query) or die (mysql_error());
  $row = mysql_fetch_array($result);

### inicializo las variables

foreach($row as $clave => $valor)
      {$row[$clave]=trim(htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1"));
      }

    $ape_y_nom=$row['ape_y_nom'];
    $e_mail=$row['e_mail'];
    $area_id=$row['area_id'];
    $piso=$row['piso'];
    $planta=$row['planta'];


    if ($row['activo']=="S")
        {$activo="S";
         $active_check="checked";
        }
    else
        {$activo="N";
         $active_check="";
        }

?>
