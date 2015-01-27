<?xml version='1.0'?>
<Project Type="Project" LVVersion="8508002">
   <Item Name="My Computer" Type="My Computer">
      <Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
      <Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
      <Property Name="server.tcp.enabled" Type="Bool">false</Property>
      <Property Name="server.tcp.port" Type="Int">0</Property>
      <Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
      <Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
      <Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
      <Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
      <Property Name="specify.custom.address" Type="Bool">false</Property>
      <Item Name="scalerstart.vi" Type="VI" URL="../../scalerstart.vi"/>
      <Item Name="4to8letterNoCR.vi" Type="VI" URL="../../../My Documents/vme/LV85_DAQ_V785_V792/4to8letterNoCR.vi"/>
      <Item Name="HistoArrayBuilder(SubVI).vi" Type="VI" URL="../../../My Documents/vme/LV85_DAQ_V785_V792/HistoArrayBuilder(SubVI).vi"/>
      <Item Name="Lab501project.vi" Type="VI" URL="Lab501project.vi"/>
      <Item Name="Dependencies" Type="Dependencies">
         <Item Name="vi.lib" Type="Folder">
            <Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
            <Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
            <Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
            <Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
            <Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
            <Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
            <Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
            <Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
            <Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
            <Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
            <Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
            <Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
            <Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
            <Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
            <Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
            <Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
            <Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
            <Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
            <Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
            <Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
            <Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
            <Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
            <Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
            <Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
            <Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
            <Item Name="General Error Handler CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler CORE.vi"/>
            <Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
            <Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
            <Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
            <Item Name="System Exec.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/system.llb/System Exec.vi"/>
         </Item>
         <Item Name="XX-USB_VME_read_16.vi" Type="VI" URL="../../../My Documents/vme/UC/XX-USB_CD3_3/LabView/LV71 VM-USB/XX-USB_VME_read_16.vi"/>
         <Item Name="XX-USB_close.vi" Type="VI" URL="../../../My Documents/vme/UC/XX-USB_CD3_3/LabView/LV71 VM-USB/XX-USB_close.vi"/>
         <Item Name="XX-USB_VME_write_16.vi" Type="VI" URL="../../../../../XX-USB_CD3_5/LabView/XX-USB_LV8.5/Library/XX-USB_VME_write_16.vi"/>
         <Item Name="XX-USB_VME_read_32.vi" Type="VI" URL="../../../My Documents/vme/UC/XX-USB_CD3_3/LabView/LV71 VM-USB/XX-USB_VME_read_32.vi"/>
         <Item Name="XX-USB_open.vi" Type="VI" URL="../../../My Documents/vme/UC/XX-USB_CD3_3/LabView/LV71 VM-USB/XX-USB_open.vi"/>
         <Item Name="Display(commands).ctl" Type="VI" URL="../Controls/Display(commands).ctl"/>
         <Item Name="Display(cluster).ctl" Type="VI" URL="../Controls/Display(cluster).ctl"/>
         <Item Name="Controler(commands).ctl" Type="VI" URL="../Controls/Controler(commands).ctl"/>
         <Item Name="Controler(cluster).ctl" Type="VI" URL="../Controls/Controler(cluster).ctl"/>
         <Item Name="OnlineManual(SubVI).vi" Type="VI" URL="OnlineManual(SubVI).vi"/>
         <Item Name="DisableVMEinterupt(SubVI).vi" Type="VI" URL="DisableVMEinterupt(SubVI).vi"/>
         <Item Name="EnableVMEinterupt(SubVI).vi" Type="VI" URL="EnableVMEinterupt(SubVI).vi"/>
         <Item Name="CleartVMEinterrupt(SubVI).vi" Type="VI" URL="CleartVMEinterrupt(SubVI).vi"/>
         <Item Name="RequestRegister(SubVI).vi" Type="VI" URL="RequestRegister(SubVI).vi"/>
         <Item Name="ScaleClear(SubVI).vi" Type="VI" URL="ScaleClear(SubVI).vi"/>
         <Item Name="ScaleStatusRegister(SubVI).vi" Type="VI" URL="ScaleStatusRegister(SubVI).vi"/>
         <Item Name="InteruptLevel&amp;VETOregister (SubVI).vi" Type="VI" URL="InteruptLevel&amp;VETOregister (SubVI).vi"/>
         <Item Name="InteruptVectorRegister (SubVI).vi" Type="VI" URL="InteruptVectorRegister (SubVI).vi"/>
         <Item Name="VMEvetoSet(SubVI).vi" Type="VI" URL="VMEvetoSet(SubVI).vi"/>
         <Item Name="VMEvetoReset(SubVI).vi" Type="VI" URL="VMEvetoReset(SubVI).vi"/>
         <Item Name="ScaleIncrease(SubVI).vi" Type="VI" URL="ScaleIncrease(SubVI).vi"/>
         <Item Name="XX-USB_VME_write_32.vi" Type="VI" URL="../../../../../XX-USB_CD3_5/LabView/XX-USB_LV8.5/Library/XX-USB_VME_write_32.vi"/>
         <Item Name="XX-USB_VME_Register_write.vi" Type="VI" URL="../../../../../XX-USB_CD3_5/LabView/XX-USB_LV8.5/Library/XX-USB_VME_Register_write.vi"/>
         <Item Name="XX-USB_VME_Output.vi" Type="VI" URL="../../../../../XX-USB_CD3_5/LabView/XX-USB_LV8.5/Library/XX-USB_VME_Output.vi"/>
         <Item Name="sub_StackWrite.vi" Type="VI" URL="../../../My Documents/sub_StackWrite.vi"/>
         <Item Name="XX-USB_Stack_write.vi" Type="VI" URL="../../../../../XX-USB_CD3_5/LabView/XX-USB_LV8.5/Library/XX-USB_Stack_write.vi"/>
         <Item Name="XX-USB_DAQ_start.vi" Type="VI" URL="../../../../../XX-USB_CD3_5/LabView/XX-USB_LV8.5/Library/XX-USB_DAQ_start.vi"/>
         <Item Name="4to8letter.vi" Type="VI" URL="../../../My Documents/vme/LV85_DAQ_V785_V792/4to8letter.vi"/>
         <Item Name="XX-USB_DAQ_stop.vi" Type="VI" URL="../../../../../XX-USB_CD3_5/LabView/XX-USB_LV8.5/Library/XX-USB_DAQ_stop.vi"/>
         <Item Name="Counter (SubVI).vi" Type="VI" URL="Counter (SubVI).vi"/>
         <Item Name="lvanlys.dll" Type="Document" URL="../../../../../Program Files/National Instruments/LabVIEW 8.5/resource/lvanlys.dll"/>
         <Item Name="XX-USB_Read_FIFO.vi" Type="VI" URL="../../../../../XX-USB_CD3_5/LabView/XX-USB_LV8.5/Library/XX-USB_Read_FIFO.vi"/>
         <Item Name="fillsetup(SubVI).vi" Type="VI" URL="../../../My Documents/vme/LV85_DAQ_V785_V792/fillsetup(SubVI).vi"/>
         <Item Name="libxxusb.dll" Type="Document" URL="libxxusb.dll"/>
         <Item Name="systemexec" Type="VI" URL="systemexec"/>
      </Item>
      <Item Name="Build Specifications" Type="Build"/>
   </Item>
</Project>
