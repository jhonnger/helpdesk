<?PHP
/*
    Nombre: set_atrib.inc
    Autor: Julio Tuozzo
    Función: Inicializing some attributes of PHD Help Desk
    Ver: 2.12
*/

if (isset($_POST[b_desmarcar]))
    {$checked='';
    }
else
    {$checked="checked";
    }

include('setup_head.inc');
echo "<p class='now'>Ticket attributes.</p>
<form method='post' action='$_SERVER[PHP_SELF]' name='form_atrib'>
$mensaje

<p>These are suggested ticket attributes. Is probable that you need more those than they are here, to administer them you must enter to <b>PHD Help Desk</b> with administrator permission and enter the option <b><i>Administration / Attributes</i></b>, and then you can enter new attributes and activate/deactivate the already existing ones.<br /><br />
If you wish to enter all the attributes you must uncheck all of this list and to press the button <b>Initialize attributes</b>, if you press <i>Cancel</i> you will not skip this step.";

if (isset($_POST[b_desmarcar]))
    {echo "<p><input class='boton_bold'  type='submit' value='Check all' name='b_marcar'></p>";
    }
else
    {echo "<p><input class='boton_bold'  type='submit' value='uncheck all' name='b_desmarcar'></p>";
    }

for($I=0;$I<4;$I++)
    {$qJ=count($v_atributo[$I]);
     echo "<h4> Attribute class $v_clases[$I] </h4>
     <p> <b>Values:</b> <br /> \n";
     for ($J=0;$J<$qJ;$J++)
        { $in_name="in_".$v_atributo[$I][$J];
          $in_name=str_replace(" ","_",$in_name);
          echo "<input type='checkbox' name='$in_name' $checked value='1'> {$v_atributo[$I][$J]}  <br /> \n";
        }
     echo "</p>";
    }


echo "
<p><b><i>IMPORTANT:</i></b>
The attributes of the class <i>$Type</i> can be classified as well in <i>$Subtype</i>, for example, the $Type hardware can be classified in Printer, Monitor, Mouse, etc. In order to do it you will have to enter to <b>PHD Help Desk</b> with administrator permission and enter to the <b><i>Administration / Attributes</i></b> option. </p>


<p style='text-align:center'> <input class='boton_bold'  type='submit' value='Initialize attributes' name='b_atrib'></p>";

echo "
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancel' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
