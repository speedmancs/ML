$thirdParty = "thirdparty"
if (Test-Path $thirdParty)
{
    Write-Host "clean up $thirdParty folder......"
    Remove-Item $thirdParty -Force -Recurse
}

New-Item $thirdParty -type directory
Push-Location $thirdParty

Write-Host "Downloading thirdparty libraries from github......"
$libs = @("gflags", "glog", "googletest")
$sols = @("gflags", "glog", "googletest-distribution")
$links = @("https://github.com/gflags/gflags.git",
          "https://github.com/google/glog.git",
          "https://github.com/google/googletest.git")
for ($i = 0; $i -lt $libs.Length; $i ++)
{
    $lib = $libs[$i]
    $link = $links[$i]
    git clone $link
    write-host $lib
    mkdir $lib\build64; Push-Location $lib\build64
    cmake -G "Visual Studio 15 2017 Win64" ..
    Write-Host "Opening up VS solution for $lib"
    & $env:vs2017.trim("`"") "$($sols[$i]).sln"
    Pop-Location
}

Read-Host 'Please open the generated VS solution and build all the release version, after that please enter any key to continue.' | Out-Null
Pop-Location



