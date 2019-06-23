<?PHP
/*
    Nombre: user_modif.inc
    Autor: Julio Tuozzo
    Función: Valida los datos del usuario y lo modifica en la base.
    Function: Verify the data of the user data and update the database
    Ver: 2.12
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

  $usuario_id=trim(strip_tags($_POST['usuario_id']));
  $ape_y_nom=trim(strip_tags($_POST['ape_y_nom']));
  $e_mail=trim(strip_tags($_POST['e_mail']));
  $piso=trim(strip_tags($_POST['piso']));
  $planta=trim(strip_tags($_POST['planta']));
  $area_id=trim(strip_tags($_POST['area_id']));
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
// Valid the data before modifing

    if (strlen($ape_y_nom)<1)
   	    {$mensaje="$UPR_error_found $No_last_name";
	    }

    elseif (strlen($e_mail)>0 and !preg_match('#^.+@.+\\..+$#',$e_mail))
   	    {$mensaje="$UPR_error_found $No_valid_e_mail";
	    }

    elseif (strlen($area_id)<1)
   	    {$mensaje="$UPR_error_found $No_area";
	    }

        else

##  Modifico los datos en la base
        {$ape_y_nom=mysql_real_escape_string(html_entity_decode($ape_y_nom,ENT_QUOTES,"ISO-8859-1"));
	     $query="UPDATE {$MyPHD}usuario
                 SET
                 ape_y_nom='$ape_y_nom',
                 area_id='$area_id',
                 e_mail='$e_mail',
                 piso='$piso',
                 planta='$planta',
                 activo='$activo',
				 update_oper='$user',
				 update_user=null,
			     update_datetime=NOW()
			     WHERE
			     usuario_id='$usuario_id'";

                 $update=mysql_query($query) or die (mysql_error());

                // Blanqueo variables
                $mensaje=str_replace("%1%", $usuario_id,$Was_modif );
                $piso=$planta=$e_mail=$ape_y_nom=$operador=$area_id=$usuario_id='';
                $fail_modif=false;
          }


?>
