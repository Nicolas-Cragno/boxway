# Bloquea edicion de archivos compilados (.o, .exe, .dll, .a, bin/, obj/)
$jsonStr = [Console]::In.ReadToEnd()
if ($jsonStr) {
    $j = $jsonStr | ConvertFrom-Json
    $f = $j.tool_input.file_path
    if ($f -match '\.(o|exe|dll|a)$' -or $f -match '[/\\](obj|bin)[/\\]') {
        Write-Output "BLOCK: No se pueden editar archivos compilados ($f)"
        exit 2
    }
}
