<?PHP
/*
    Nombre: set_atrib.inc
    Autor: Julio Tuozzo
    Función: Inicializa algunos atributos de los tickets en PHD Help Desk
    Ver: 2.12
*/

if (isset($_POST[b_desmarcar]))
    {$checked='';
    }
else
    {$checked="checked";
    }

include('setup_head.inc');
echo "
<p class='now'>Atributos del ticket.</p>
<form method='post' action='$_SERVER[PHP_SELF]' name='form_atrib'>
$mensaje

<p>Estos son atributos del ticket sugeridos. Es probable que Ud. necesite m&aacute;s de los que
se encuentran aqui, para administrarlos debe ingresar a <b>PHD Help Desk</b> con permiso de administrador e ingresar a la opci&oacute;n
<b><i>Administraci&oacute;n / Atributos</i></b>, desde all&iacute, puede ingresar nuevos atributos y activar / desactivar los ya existentes.<br />
Si desea ingresar Ud. mismo todos los atributos debe desmarcar los de esta lista y presionar el bot&oacute;n <b>Inicializar atributos</b>, ya que si sale por la opci&oacute;n <i>Cancelar</i> no podr&aacute; saltear este paso.</p>";

if (isset($_POST[b_desmarcar]))
    {echo "<p><input class='boton_bold'  type='submit' value='Marcar todos' name='b_marcar'></p>";
    }
else
    {echo "<p><input class='boton_bold'  type='submit' value='Desmarcar todos' name='b_desmarcar'></p>";
    }

for($I=0;$I<4;$I++)
    {$qJ=count($v_atributo[$I]);
     echo "<h4> Clase de atributo: $v_clases[$I] </h4>
     <p> <b>Valores:</b> <br /> \n";
     for ($J=0;$J<$qJ;$J++)
        { $in_name="in_".$v_atributo[$I][$J];
          $in_name=str_replace(" ","_",$in_name);
          echo "<input type='checkbox' name='$in_name' $checked value='1'> {$v_atributo[$I][$J]}  <br /> \n";
        }
     echo "</p>";
    }


echo "
<p><b><i>IMPORTANTE:</i></b> Los atributos de la clase <i>$Type</i> pueden a su vez clasificarse en <i>$Subtype</i>, por ejemplo, el $Type <em>hardware</em> se puede clasificar en <em>Impresora, Monitor, Mouse,</em> etc. Para hacerlo deberá ingresar a <b>PHD Help Desk</b> con permiso de administrador e ingresar a la opci&oacute;n
<b><i>Administraci&oacute;n / Atributos</i></b>.</p>

<p style='text-align:center'> <input class='boton_bold'  type='submit' value='Inicializar atributos' name='b_atrib'></p>";

echo "
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancelar' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
