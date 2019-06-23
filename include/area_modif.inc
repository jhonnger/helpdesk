<?PHP
/*
    Nombre: area_modif.inc
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Modifica los datos de un área
    Function: Modify the area's data
    Ver:2.00
    
*/


$fail_modif=true;

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

$area_id=$_POST[area_id];
$nombre=$_POST[nombre];

if ($_POST[activo]=="1")
        {$activo="S";
         $active_check="checked";
        }
else
        {$activo="N";
         $active_check="";
        }


## Valido los datos antes de modificarlos
// Verify the data before insert its

if (strlen($nombre)<1)
     	{$mensaje="$Blank_name";
        }
elseif ($activo=="N")
        { ## Verifico que no existan usuarios en el área
          // Verify that doesn't exists users in the area.

          $query="SELECT usu.*
            FROM {$MyPHD}usuario usu
            JOIN {$MyPHD}area are ON usu.area_id=are.area_id
            WHERE are.activo='S'
            AND usu.activo='S'
            AND usu.area_id='$area_id'";

           $result=mysql_query($query) or die ($No_database);
           $q_usuarios=mysql_num_rows($result);

           if ($q_usuarios>0)
                {$mensaje="$Are_users_in $area_id";
                }
         }
if (strlen($mensaje)<9)
    {## Ejecuto el query de actualización
     // Execute the update query
     $nombre=mysql_real_escape_string(html_entity_decode($nombre,ENT_QUOTES,"ISO-8859-1"));
     $query="UPDATE {$MyPHD}area
             SET activo='$activo', nombre='$nombre', update_oper='$_SESSION[PHD_OPERADOR]', update_datetime=NOW()
             WHERE area_id='$area_id'";
     $update=mysql_query($query) or die (mysql_error());
     $mensaje=str_replace("%1%", $area_id,$Was_modif );
     $area_id=$nombre="";
     $fail_modif=false;
    }


?>
