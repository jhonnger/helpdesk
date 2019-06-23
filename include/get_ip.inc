<?PHP
/*
    Nombre: get_ip.php
    Autor: desconocido
    Función: función que devuelve la dirección IP del cliente
    Ver: 1.1
*/

function get_ip ()

    {if ($_SERVER)
        {if ( $_SERVER[HTTP_X_FORWARDED_FOR] )
            {$realip = $_SERVER["HTTP_X_FORWARDED_FOR"];
            }
        elseif ( $_SERVER["HTTP_CLIENT_IP"] )
            {$realip = $_SERVER["HTTP_CLIENT_IP"];
          }
        else
            {$realip = $_SERVER["REMOTE_ADDR"];
            }
        }
    else
        {if ( getenv( "HTTP_X_FORWARDED_FOR" ) )
            {$realip = getenv( "HTTP_X_FORWARDED_FOR" );
            }
         elseif ( getenv( "HTTP_CLIENT_IP" ) )
            {$realip = getenv( "HTTP_CLIENT_IP" );
            }
         else {$realip = getenv( "REMOTE_ADDR" );
              }
        }
    return $realip;
    }
?>
