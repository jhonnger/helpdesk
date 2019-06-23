<?PHP
/*
    Nombre: area_insert.inc
    Autor: Julio Tuozzo
    Función: Inserta el área en la tabla
    Function: Inserts the area in the table
    Ver: 2.05
*/

## Preparo los datos para modificar
// Prepare the data to modify

if (get_magic_quotes_gpc())
     { foreach($_POST as $clave => $valor)
         {$_POST[$clave]=stripslashes($_POST[$clave]);
         }
     }
foreach($_POST as $clave => $valor)
      {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
      }

$area_id=$_POST['area_id'];
$nombre=$_POST['nombre'];
$user=$_SESSION['PHD_OPERADOR'];

if ($_POST[activo]=="1")
        {$activo="S";
         $active_check="checked";
        }
else
        {$activo="N";
         $active_check="";
        }

## Valido datos antes de darlos de alta
// Valid the data before insert


   if (strlen($area_id)<1)
    	{$mensaje=$No_area;
        }
   elseif (!preg_match('#^[-_a-zA-Z0-9]+$#', $area_id))
     	{$mensaje="$area_id $Invalid_character";
        }

   elseif (strlen($nombre)<1)
     	{$mensaje="$Blank_name";
        }
   else
   
        {## Verifico que no exista
         // Check that not exists
   
        $query="SELECT * FROM {$MyPHD}area WHERE area_id='$area_id'";
        $result=mysql_query($query) or die (mysql_error());
   
        if (mysql_num_rows($result)>0)
                {$mensaje="$Area_exists";
                }
        else

            ##  Lo doy de alta en la base
            {## Armo el query y lo ejecuto
             $area=mysql_real_escape_string(html_entity_decode($area,ENT_QUOTES,"ISO-8859-1"));
             $nombre=mysql_real_escape_string(html_entity_decode($nombre,ENT_QUOTES,"ISO-8859-1"));

             $query="INSERT INTO {$MyPHD}area VALUES
                       ('$area_id',
					   '$nombre',
					   '$activo',
					   '$user',
					   NOW(),
					   '$user',
					   NOW())";

            $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
            $insert=mysql_query($query) or die (mysql_error());
            $mensaje=str_replace("%1%", "$area_id - $nombre ",$Was_loaded );
            // Blanqueo variables
            $area_id=$nombre='';
            }
        }

?>
