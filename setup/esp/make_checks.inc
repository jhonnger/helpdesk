<?PHP
/*
    Nombre: make_checks.inc
    Autor: Julio Tuozzo
    Función: Controles de la instalación.
    Ver: 2.12
*/



## 1. Verifico que estén disponibles las librerías MySQL y GD

if (!function_exists('mysql_connect'))
    { echo "<p class='danger'>ERROR -
    No se encuentran disponibles las funciones de acceso a la base de datos MySQL desde PHP.<br/>
            Verifique la instalaci&oacute;n de su servidor.</p>
            <p class = 'danger'> Proceso de configuración de <b>PHD Help Desk</b> suspendido, solucione el problema e intente nuevamente. </p> ";
      exit();
    }

if (!function_exists('gd_info'))
    { echo "<p class='danger'>ERROR -
    No se encuentra disponible la liber&iacute;a para gr&aacute;ficos GD.<br/>
            Verifique la instalaci&oacute;n de su servidor.</p>
            <p class = 'danger'> Proceso de configuración de <b>PHD Help Desk</b> suspendido, solucione el problema e intente nuevamente. </p> ";
      exit();
    }

require('../../include/lang.inc');
require('../../config.inc.php');

## 2. Verifico que los archivos phd.inc y lang.inc correspondan a la versión 2.12

if ($VPHD!="2.12")
    {echo "<p class='danger'> Error: el archivo config.inc.php no corresponde a la versi&oacute;n 2.12 de <b>PHD Help Desk</b></p>
    <p> Puede suceder que tenga otra instalaci&oacute;n de <b>PHD Help Desk</b> en su servidor y que la variable <i>include_path</i> del archivo <i>php.ini</i> se encuentre configurada para ese subdirecotrio.</p>
     <p class = 'danger'> Proceso de configuración de <b>PHD Help Desk</b> suspendido, solucione el problema e intente nuevamente. </p>";

    exit();
    }

if ($Vlang!="2.12")
    {echo "<p class='danger'> Error: el archivo $path_lang lang.inc no corresponde a la versi&oacute;n 2.12 de <b>PHD Help Desk</b></p>
    <p> Puede suceder que tenga otra instalaci&oacute;n de <b>PHD Help Desk</b> en su servidor y que la variable <i>include_path</i> del archivo <i>php.ini</i> se encuentre configurada para ese subdirectorio.</p>
       <p class = 'danger'> Proceso de configuración de <b>PHD Help Desk</b> suspendido, solucione el problema e intente nuevamente. </p>";
    exit();
    }

## 3. Verifico que ya se haya especificado el lenguaje.

    if (!isset($Contact) or !isset($Process) or !isset($State) or !isset($Type))
        { $c_lang='now';
          $c_base_dato=$c_param=$c_create=$c_mail=$c_admin=$c_atrib='danger';
        }
    else
        {$c_lang='ok';

## 4. Verifico los parámetros de acceso a la base de datos.
         if(!@mysql_connect($Host,$Usuario,$Contrasena) or !@mysql_select_db($Base))
            {$c_base_dato='now';
             $c_param=$c_create=$c_mail=$c_admin=$c_atrib='danger';
            }
         else
            { $c_base_dato='ok';


## 5. Verifico que esten creadas las tablas en la base.
              $tablas="(area)(atributo)(ticket)(hist_pass)(operador)(parametros)(sector)(sigo_ticket)(solicitud)(usuario)(e_mail_error)";
              $query="SHOW TABLES";
              $result=mysql_query($query) or die ("<p class='danger'> ERROR EN QUERY </p>".mysql_error());
              while ($row = mysql_fetch_array($result))
                    {$tablas=str_replace("(".$row[0].")","",$tablas);
                    }
              if (strlen($tablas)>1)
                    {$c_create='now';
                     $c_param=$c_mail=$c_admin=$c_atrib='danger';
                    }
              else
                    {$c_create='ok';


## 6. Verifico que este configurado para enviar correo electrónico

              if ($Mail_host == 'your.mail.server.com' or $Mail_usuario == 'your_e_mail_user@mail.com')
                    {$c_mail='now';
                     $c_param=$c_admin=$c_atrib='danger';
                    }
              else
                    {$c_mail='ok';



## 7. Verifico que haya algún operador con permiso de administrador.
                     $query="SELECT * FROM operador WHERE nivel>=20";
                     $result=mysql_query($query) or die ("<p class='danger'> ERROR EN QUERY </p>".mysql_error());
                     $q_admin=mysql_num_rows($result);

                     if ($q_admin<1)
                        {$c_admin='now';
                         $c_param=$c_atrib='danger';
                        }
                     else
                        {$c_admin='ok';

## 8. Verifico que se hayan ingresado atributos.

                         if ($PHD_Ins=="NO")
                            {$c_atrib='now';
                             $c_param='danger';
                            }
                         else
                            {$c_atrib='ok';
## 9. Verifico que se hayan configurado los parámetros generales.
                             $query="SELECT * FROM parametros";
                             $result=mysql_query($query) or die ("<p class='danger'> ERROR EN QUERY </p>".mysql_error());
                             $q_param=mysql_num_rows($result);

                             if($q_param<1)
                                {$c_param='now';
                                }
                             else
                                {$c_param='ok';


                                }
                            }
                        }
                    }
                }
            }
        }



?>
