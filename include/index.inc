<?PHP
/*
    Nombre: index.inc
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Vista del menú principal
    Function: Main menu view.
    Ver: 2.00
*/

require('head.inc');
echo"  <body>";

require('f_fecha_JS.inc');

## Valido la fecha del servidor vs. la fecha del cliente donde ese esta ejecutando
## la aplicación, si hay más de $_SESSION[PHD_MAX_DIF_MIN] minutos de diferencia
## aviso y mando a la página de login para dejar en cero el permiso de acceso.
// Valid the date of the servant vs. the date of the client where that this
// executing the application, if is more than $_SESSION[PHD_MAX_DIF_MIN] minutes of difference
// warning and control to the page of login to set to zero the access permission.

## Inicializo una variable con la fecha del servidor
// Initialize a variable with the date of the servant

$fecha_servidor=date("F j Y H:i:s");

echo
"<SCRIPT LANGUAGE='JavaScript' >
var local= new Date();
var servidor=new Date('$fecha_servidor');

if ((Math.abs(servidor-local)/60000)>$_SESSION[PHD_MAX_DIF_MIN])
    {window.alert('$Date_client_server_error'+f_fecha(servidor));";
if ($_SESSION['PHD_NIVEL'] != 20)
     {echo "window.location='login.php';";
     }
echo "    }
</script> \n";
require('menu.inc');
require('ticket_selector.inc');
require('ticket_display.inc');
?>
