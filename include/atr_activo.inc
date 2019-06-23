<?PHP
/*
    Nombre: atr_activo.inc
    Autor: Julio Tuozzo
    Función: Pasa un atributo de "Activo" a "Inactivo" y vice versa
    Function: It passes an attribute of “Active” to “Inactive” and vice turns.
    Ver:2.00
    
*/

## Verifico que el atributo a desactivar no corresponda con uno de los valores por deafult
// Check that the attribute do not corresponding a default value.

$seq_atrib_id=$_POST['activo'];
$query="SELECT atributo, valor FROM {$MyPHD}atributo WHERE seq_atrib_id=$seq_atrib_id";
$result=mysql_query($query) or die (mysql_error());
$row = mysql_fetch_array($result);

$query="SELECT * FROM {$MyPHD}parametros";
$result=mysql_query($query) or die (mysql_error());
$param = mysql_fetch_array($result);

switch ($row['atributo'])
    {case $Contact:
         $default_val=$param['contact_default'];
     break;
     case $Process:
        $default_val=$param['process_default'];
     break;
     case $State:
        $default_val=$param['state_default'];
        if ($row['valor']==$param['state_alert'])
            {$default_val=$row['valor'];
            }
        elseif ($row['valor']==$param['main_screen_state'])
            {$default_val=$row['valor'];
            }

     break;
     
     default:
        $default_val="";
    }

if($row['valor']==$default_val)
        {$mensaje=str_replace("%1%",$row['atributo'],$No_modif_attrib);
         $mensaje=str_replace("%2%",$row['valor'],$mensaje);
        }


if (strlen($mensaje)<7)

    {## Ejecuto el query de actualización

    $query="UPDATE {$MyPHD}atributo
            SET activo=IF(activo='S','N','S'), update_oper='$_SESSION[PHD_OPERADOR]', update_datetime=NOW()
            WHERE seq_atrib_id=$seq_atrib_id";
    $update=mysql_query($query) or die (mysql_error());
    }

?>
