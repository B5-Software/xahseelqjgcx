Write-Host "�����г������п�¼ȡ���API������ Powershell�� V2"

$year = Read-Host "�������ѯ��ݣ�"
$zkzh = Read-Host "������׼��֤�ţ�"
$sfzh = Read-Host "���������֤�ţ�"


$url = "http://222.91.162.190:7173/OperatorData.ashx?Type=MTC&YearID=$year&Zkzh=$zkzh&Code=&r=100&Sfzh=$sfzh"
try {
    $response = Invoke-RestMethod -Uri $url -Method Get
} catch {
    Write-Host "����ʧ�ܣ�$_"
    exit
}


if (-not $response) {
    Write-Host "����ʧ��"
    exit
}


Write-Host "��ѯ�ɹ�������Ϊ�嵥���ݣ�"

if ($response.sfzh) {
    Write-Host ("���֤�ţ�" + $response.sfzh)
} else {
    Write-Host "���֤�ţ�N/A"
}

if ($response.xm) {
    Write-Host ("������" + $response.xm)
} else {
    Write-Host "������N/A"
}

if ($response.byxxdm) {
    Write-Host ("��ҵѧУ���룺" + $response.byxxdm)
} else {
    Write-Host "��ҵѧУ���룺N/A"
}

if ($response.lqpc) {
    Write-Host ("¼ȡ���Σ�" + $response.lqpc)
} else {
    Write-Host "¼ȡ���Σ�N/A"
}

if ($response.clqpc) {
    Write-Host ("¼ȡѧУ���ͣ�" + $response.clqpc)
} else {
    Write-Host "¼ȡѧУ���ͣ�N/A"
}

if ($response.lqlb) {
    Write-Host ("¼ȡ���" + $response.lqlb)
} else {
    Write-Host "¼ȡ���N/A"
}

if ($response.clqlb) {
    Write-Host ("¼ȡ������֣�" + $response.clqlb)
} else {
    Write-Host "¼ȡ������֣�N/A"
}

if ($response.xxdm) {
    Write-Host ("¼ȡѧУ���룺" + $response.xxdm)
} else {
    Write-Host "¼ȡѧУ���룺N/A"
}

if ($response.xxmc) {
    Write-Host ("¼ȡѧУ��" + $response.xxmc)
} else {
    Write-Host "¼ȡѧУ��N/A"
}

if ($response.totaltime) {
    Write-Host ("��ѯ��ʱ��" + $response.totaltime)
} else {
    Write-Host "��ѯ��ʱ��N/A"
}

Write-Host "����Ϊ�嵥���ݡ���¼ȡѧУֵΪ�գ�������¼ȡ��Ϣ����˶���Ϣ�Ƿ���ȷ�������Ϣ���������ĵȴ���һ����¼ȡ��"
Write-Host "This is a Free and Open Source Software (GPL-3.0)."
Write-Host "Made by B5-Software"

Read-Host "���س����˳�..."
