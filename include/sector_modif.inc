<?PHP
/*
    Nombre: sector_modif.inc
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Modifica los datos de un sector
    Function: Modify the sector's data
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

$sector_id=$_POST[sector_id];
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
        { ## Verifico que no existan operadores en el sector
          // Verify that doesn't exists operators in the sector.

          $query="SELECT ope.*
            FROM {$MyPHD}operador ope
            JOIN {$MyPHD}sector sec ON ope.sector_id=sec.sector_id
            WHERE sec.activo='S'
            AND ope.nivel>0
            AND ope.sector_id='$sector_id'";

           $result=mysql_query($query) or die (mysql_error());
           $q_usuarios=mysql_num_rows($result);

           if ($q_usuarios>0)
                {$mensaje="$Are_opers_in $sector_id";
                }
         }
if (strlen($mensaje)<9)
    {## Ejecuto el query de actualización
     // Execute the update query
     $nombre=mysql_real_escape_string(html_entity_decode($nombre,ENT_QUOTES,"ISO-8859-1"));
     $query="UPDATE {$MyPHD}sector
             SET activo='$activo', nombre='$nombre', update_oper='$_SESSION[PHD_OPERADOR]', update_datetime=NOW()
             WHERE sector_id='$sector_id'";
     $update=mysql_query($query) or die (mysql_error());
     $mensaje=str_replace("%1%", $sector_id,$Was_modif );
     $sector_id=$nombre="";
     $fail_modif=false;
    }
?>
