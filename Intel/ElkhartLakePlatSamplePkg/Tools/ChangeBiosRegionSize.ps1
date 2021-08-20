$xml  = New-Object XML 
$xml.Load($args[0])
$xml.ftoolRoot.Chipset.Region1.RegionLength.value="0x00" + [Convert]::ToString($args[1], 16)
$xml.Save($args[0])

