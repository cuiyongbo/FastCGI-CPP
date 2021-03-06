*************
FastCGI howto
*************

#. install `nginx`, `spawn-fcgi`.
   
#. configure nginx.
   
    .. code-block:: none

        http 
        {
            server 
            {
                listen 80;
                server_name localhost;
        
                location /hello 
                {
                    fastcgi_pass   127.0.0.1:8000;
                    fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
                    fastcgi_param  SERVER_SOFTWARE    nginx;
                    fastcgi_param  QUERY_STRING       $query_string;
                    fastcgi_param  REQUEST_METHOD     $request_method;
                    fastcgi_param  CONTENT_TYPE       $content_type;
                    fastcgi_param  CONTENT_LENGTH     $content_length;
                    fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
                    fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
                    fastcgi_param  REQUEST_URI        $request_uri;
                    fastcgi_param  DOCUMENT_URI       $document_uri;
                    fastcgi_param  DOCUMENT_ROOT      $document_root;
                    fastcgi_param  SERVER_PROTOCOL    $server_protocol;
                    fastcgi_param  REMOTE_ADDR        $remote_addr;
                    fastcgi_param  REMOTE_PORT        $remote_port;
                    fastcgi_param  SERVER_ADDR        $server_addr;
                    fastcgi_param  SERVER_PORT        $server_port;
                    fastcgi_param  SERVER_NAME        $server_name;
                }

                location /test
                { 
                    root html; 
                    fastcgi_pass unix:/tmp/hello.sock;
                    fastcgi_index index.php; 
                    fastcgi_param SCRIPT_FILENAME /scripts$fastcgi_script_name; 
                    include fastcgi_params; 
                }
            }
        }

#. Compile program demo: ``g++ hello_world.cpp -o hello -lfcgi``.

#. Start it with: 
   
   * ``spawn -p 8000 -n hello`` for TCP Port;
   * ``spawn-fcgi -s /tmp/hello.sock -M 0666 hello`` for unix domain socket.
   
.. rubric:: Footnotes

.. [#] `FastCGI repository <https://fastcgi-archives.github.io/>`_
.. [#] `NGINX FastCGI example <http://nginx.org/en/docs/http/ngx_http_fastcgi_module.html#example>`_
.. [#] `NGINX Connect Cpp FastCGI <http://chriswu.me/blog/writing-hello-world-in-fcgi-with-c-plus-plus/>`_