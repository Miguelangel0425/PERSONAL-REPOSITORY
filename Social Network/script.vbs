' Función para generar una clave aleatoria de 16 caracteres (puedes ajustar la longitud)
Function GenerateLicenseKey()
    Dim i, key, rand
    key = ""
    For i = 1 To 16
        ' Genera un número aleatorio entre 1 y 36
        rand = Int((36 * Rnd) + 1)
        If rand <= 26 Then
            ' Si es entre 1 y 26, obtiene una letra mayúscula (A-Z)
            key = key & Chr(64 + rand)
        Else
            ' Si es mayor, obtiene un dígito (0-9)
            key = key & CStr(rand - 26)
        End If
    Next
    GenerateLicenseKey = key
End Function

' Inicializar semilla para Rnd
Randomize

Dim licenseKeys(), i, keyText
ReDim licenseKeys(9) ' Array para 10 claves

' Genera 10 claves y las almacena en el array
For i = 0 To 9
    licenseKeys(i) = GenerateLicenseKey()
    keyText = keyText & licenseKeys(i) & vbCrLf
Next

' Obtener la ruta del escritorio del usuario
Dim shell, desktopPath
Set shell = CreateObject("WScript.Shell")
desktopPath = shell.SpecialFolders("Desktop")

' Crear y escribir el archivo "licencias.txt" en el escritorio
Dim fso, file
Set fso = CreateObject("Scripting.FileSystemObject")
Set file = fso.CreateTextFile(desktopPath & "\licencias.txt", True)
file.Write keyText
file.Close

' Solicitar al usuario la clave de licencia
Dim userKey
userKey = InputBox("Ingrese su clave de licencia:")

' Validar que la clave ingresada coincida con alguna de las generadas
Dim valid
valid = False
For i = 0 To UBound(licenseKeys)
    If userKey = licenseKeys(i) Then
        valid = True
        Exit For
    End If
Next

If Not valid Then
    MsgBox "Clave de licencia no válida. La instalación se cancelará."
    ' Cancela la instalación (esto dependerá de cómo Smart Install Maker gestione los abortos)
    WScript.Quit
End If

' Si la clave es válida, continúa con la instalación
' Aquí se puede continuar con el resto del proceso
