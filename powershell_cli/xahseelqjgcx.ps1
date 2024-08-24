Write-Host "西安市城六区中考录取结果API调用器 Powershell版 V2"

$year = Read-Host "请输入查询年份："
$zkzh = Read-Host "请输入准考证号："
$sfzh = Read-Host "请输入身份证号："


$url = "http://222.91.162.190:7173/OperatorData.ashx?Type=MTC&YearID=$year&Zkzh=$zkzh&Code=&r=100&Sfzh=$sfzh"
try {
    $response = Invoke-RestMethod -Uri $url -Method Get
} catch {
    Write-Host "请求失败：$_"
    exit
}


if (-not $response) {
    Write-Host "请求失败"
    exit
}


Write-Host "查询成功，以下为清单数据："

if ($response.sfzh) {
    Write-Host ("身份证号：" + $response.sfzh)
} else {
    Write-Host "身份证号：N/A"
}

if ($response.xm) {
    Write-Host ("姓名：" + $response.xm)
} else {
    Write-Host "姓名：N/A"
}

if ($response.byxxdm) {
    Write-Host ("毕业学校代码：" + $response.byxxdm)
} else {
    Write-Host "毕业学校代码：N/A"
}

if ($response.lqpc) {
    Write-Host ("录取批次：" + $response.lqpc)
} else {
    Write-Host "录取批次：N/A"
}

if ($response.clqpc) {
    Write-Host ("录取学校类型：" + $response.clqpc)
} else {
    Write-Host "录取学校类型：N/A"
}

if ($response.lqlb) {
    Write-Host ("录取类别：" + $response.lqlb)
} else {
    Write-Host "录取类别：N/A"
}

if ($response.clqlb) {
    Write-Host ("录取类别文字：" + $response.clqlb)
} else {
    Write-Host "录取类别文字：N/A"
}

if ($response.xxdm) {
    Write-Host ("录取学校代码：" + $response.xxdm)
} else {
    Write-Host "录取学校代码：N/A"
}

if ($response.xxmc) {
    Write-Host ("录取学校：" + $response.xxmc)
} else {
    Write-Host "录取学校：N/A"
}

if ($response.totaltime) {
    Write-Host ("查询用时：" + $response.totaltime)
} else {
    Write-Host "查询用时：N/A"
}

Write-Host "以上为清单数据。如录取学校值为空，则暂无录取信息。请核对信息是否正确。如果信息无误，请耐心等待新一批的录取。"
Write-Host "This is a Free and Open Source Software (GPL-3.0)."
Write-Host "Made by B5-Software"

Read-Host "按回车键退出..."
