<?PHP
/*
    Nombre: clave_chg.inc
    Autor: Julio Tuozzo
    Función: Formulario de cambio de contraseña
    Function: Change password form.
    Version: 2.12

*/

if($_SESSION['PHD_NIVEL']>4)
    {$opcion=$Oper_pswd_change;
     $menu="menu.inc";
    }
else
    {$opcion="<h2>$Passwd_change</h2>";
     $menu="user_menu.inc";
    }

include('head.inc');
echo "<body>";
include($menu);

$ancho=22+(strlen($Change)*9);
echo "
<div id='contenido'>
<p class='error'> $mensaje </p>
<div id='login'>
    <form method='post' action='$_SERVER[PHP_SELF]' >
      $Actual_pswd: <input type='password' name='actual' size='16' maxlength='16'> <br />  <br />
      $New_pswd:  <input type='password' name='nueva' size='16'maxlength='16'> <br />  <br />
      $Retype_pswd: <input type='password' name='reingresa' size='16'maxlength='16'> <br />  <br />

        <input class='boton_guardar'  style='width: {$ancho}px;' type='submit' value='$Change' name='cambiar' />";

## Valido el nivel de ejecución para ver si el cambio de contraseña es obligatorio,
## en caso de no ser obligatorio lo dejo cancelar
// Check the level of execution to see if the change of password is obligatory,
// in case of being obligatory do not let it cancel


        if ($_SESSION['PHD_NIVEL']>5)
            {$ancho=25+(strlen($Home)*9);
              echo"\n &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <input class='boton_salir' style='width: {$ancho}px;' type='submit' value='$Home' name='salir' />";
            }
echo "
    </form>

</div>
</div>
</body>
</html>";
?>
