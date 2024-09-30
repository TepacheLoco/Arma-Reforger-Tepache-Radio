//------------------------------------------------------------------------------------------------
//! Scripted VON input and control, attached to SCR_PlayerController
modded class SCR_VONController : ScriptComponent
{
 	// TODO more robust von component selection management

	[Attribute(defvalue: "Sounds/VON/Samples/Radio_Start_1.wav", params: "wav")]
	protected ResourceName m_sRadioSound0;
	[Attribute(defvalue: "Sounds/VON/Samples/Radio_Start_2.wav", params: "wav")]
	protected ResourceName m_sRadioSound1;
	[Attribute(defvalue: "Sounds/VON/Samples/Radio_Start_3.wav", params: "wav")]
	protected ResourceName m_sRadioSound2;
	[Attribute(defvalue: "Sounds/VON/Samples/Radio_Start_4.wav", params: "wav")]
	protected ResourceName m_sRadioSound3;
	
	[Attribute(defvalue: "Sounds/VON/Samples/Radio_End_1.wav", params: "wav")]
	protected ResourceName m_sRadioSoundEnd0;
	[Attribute(defvalue: "Sounds/VON/Samples/Radio_End_2.wav", params: "wav")]
	protected ResourceName m_sRadioSoundEnd1;
	[Attribute(defvalue: "Sounds/VON/Samples/Radio_End_3.wav", params: "wav")]
	protected ResourceName m_sRadioSoundEnd2;
	[Attribute(defvalue: "Sounds/VON/Samples/Radio_End_4.wav", params: "wav")]
	protected ResourceName m_sRadioSoundEnd3;
	
	protected AudioHandle m_AudioHandleRadioSqawk;
	protected AudioHandle m_AudioHandleRadioSqawkRadioSqawkOff;
	
	//------------------------------------------------------------------------------------------------
	//! VON channel speech listener callback
 	override protected void OnVONChannel(float value, EActionTrigger reason)
	{
		if (reason == EActionTrigger.DOWN)
		{
			m_bIsActiveModeLong = false;
			if (!AudioSystem.IsSoundPlayed(m_AudioHandleRadioSqawk))
					AudioSystem.TerminateSound(m_AudioHandleRadioSqawk);
			
			RandomGenerator gen = new RandomGenerator();
			int sampleRadioStartIndex =  gen.RandIntInclusive(0, 3);
			
			if (sampleRadioStartIndex==0)
				m_AudioHandleRadioSqawk = AudioSystem.PlaySound(m_sRadioSound0);	
			if (sampleRadioStartIndex==1)
				m_AudioHandleRadioSqawk = AudioSystem.PlaySound(m_sRadioSound1);	
			if (sampleRadioStartIndex==2)
				m_AudioHandleRadioSqawk = AudioSystem.PlaySound(m_sRadioSound2);	
			if (sampleRadioStartIndex==3)
				m_AudioHandleRadioSqawk = AudioSystem.PlaySound(m_sRadioSound3);			
			
			VONChannel(true);
		}
		else {
				AudioSystem.TerminateSound(m_AudioHandleRadioSqawk);
				
				if (!AudioSystem.IsSoundPlayed(m_AudioHandleRadioSqawkRadioSqawkOff))
						AudioSystem.TerminateSound(m_AudioHandleRadioSqawkRadioSqawkOff);
				
			
				RandomGenerator gen = new RandomGenerator();
				int sampleRadioEndIndex =  gen.RandIntInclusive(0, 3);
				
				if (sampleRadioEndIndex==0)
					m_AudioHandleRadioSqawkRadioSqawkOff = AudioSystem.PlaySound(m_sRadioSoundEnd0);	
				if (sampleRadioEndIndex==1)
					m_AudioHandleRadioSqawkRadioSqawkOff = AudioSystem.PlaySound(m_sRadioSoundEnd1);	
				if (sampleRadioEndIndex==2)
					m_AudioHandleRadioSqawkRadioSqawkOff = AudioSystem.PlaySound(m_sRadioSoundEnd2);	
				if (sampleRadioEndIndex==3)
					m_AudioHandleRadioSqawkRadioSqawkOff = AudioSystem.PlaySound(m_sRadioSoundEnd3);	
			
				VONChannel(false);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//! VON switch between direct/channel mode
 	override protected void OnVONSwitch(float value, EActionTrigger reason)
	{
		m_bIsActiveModeDirect = !m_bIsActiveModeDirect;
		
		if (m_bIsToggledDirect || m_bIsToggledChannel)
			OnVONToggleGamepad(0, EActionTrigger.UP);
		else
		{
			OnVONGamepad(0, EActionTrigger.PRESSED); 
			GetGame().GetCallqueue().CallLater(OnVONGamepad, 100, false, 0, EActionTrigger.UP);	// visualisation of switching from direct to radio VON when using controller
		}
	}
	
	//------------------------------------------------------------------------------------------------
};
