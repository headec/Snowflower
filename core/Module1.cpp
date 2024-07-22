///////////////////////////////////////////////////////////////////////////////
// Module1.cpp
#include "TcPch.h"
#pragma hdrstop

#include "Module1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
DEFINE_THIS_FILE()

///////////////////////////////////////////////////////////////////////////////
// CModule1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Collection of interfaces implemented by module CModule1
BEGIN_INTERFACE_MAP(CModule1)
	INTERFACE_ENTRY_ITCOMOBJECT()
	INTERFACE_ENTRY(IID_ITcADI, ITcADI)
	INTERFACE_ENTRY(IID_ITcWatchSource, ITcWatchSource)
///<AutoGeneratedContent id="InterfaceMap">
	INTERFACE_ENTRY(IID_ITcCyclic, ITcCyclic)
///</AutoGeneratedContent>
END_INTERFACE_MAP()


IMPLEMENT_ITCOMOBJECT(CModule1)
IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP2(CModule1)
IMPLEMENT_ITCADI(CModule1)
IMPLEMENT_ITCWATCHSOURCE(CModule1)


///////////////////////////////////////////////////////////////////////////////
// Set parameters of CModule1 
BEGIN_SETOBJPARA_MAP(CModule1)
	SETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="SetObjectParameterMap">
	SETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	SETOBJPARA_VALUE(PID_Module1State, m_State)
	SETOBJPARA_VALUE(PID_Module1Setting, m_Setting)
	SETOBJPARA_VALUE(PID_Module1Move, m_Move)
	SETOBJPARA_VALUE(PID_Module1Event, m_Event)
	SETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
///</AutoGeneratedContent>
END_SETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get parameters of CModule1 
BEGIN_GETOBJPARA_MAP(CModule1)
	GETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="GetObjectParameterMap">
	GETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	GETOBJPARA_VALUE(PID_Module1State, m_State)
	GETOBJPARA_VALUE(PID_Module1Setting, m_Setting)
	GETOBJPARA_VALUE(PID_Module1Move, m_Move)
	GETOBJPARA_VALUE(PID_Module1Event, m_Event)
	GETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
///</AutoGeneratedContent>
END_GETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get watch entries of CModule1
BEGIN_OBJPARAWATCH_MAP(CModule1)
	OBJPARAWATCH_DATAAREA_MAP()
///<AutoGeneratedContent id="ObjectParameterWatchMap">
	OBJPARAWATCH_VALUE(PID_Module1State, m_State)
	OBJPARAWATCH_VALUE(PID_Module1Setting, m_Setting)
	OBJPARAWATCH_VALUE(PID_Module1Move, m_Move)
	OBJPARAWATCH_VALUE(PID_Module1Event, m_Event)
///</AutoGeneratedContent>
END_OBJPARAWATCH_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get data area members of CModule1
BEGIN_OBJDATAAREA_MAP(CModule1)
///<AutoGeneratedContent id="ObjectDataAreaMap">
	OBJDATAAREA_VALUE(ADI_Module1Inputs, m_Inputs)
	OBJDATAAREA_VALUE(ADI_Module1Outputs, m_Outputs)
///</AutoGeneratedContent>
END_OBJDATAAREA_MAP()


///////////////////////////////////////////////////////////////////////////////
CModule1::CModule1()
	: m_Trace(m_TraceLevelMax, m_spSrv)
	, mainService_(&m_Outputs.ToIO, &m_Inputs.FromIO)
{
///<AutoGeneratedContent id="MemberInitialization">
	m_TraceLevelMax = tlAlways;
	m_State = 0;
	memset(&m_Setting, 0, sizeof(m_Setting));
	memset(&m_Move, 0, sizeof(m_Move));
	m_Event = 0;
	memset(&m_Inputs, 0, sizeof(m_Inputs));
	memset(&m_Outputs, 0, sizeof(m_Outputs));
///</AutoGeneratedContent>
}

///////////////////////////////////////////////////////////////////////////////
CModule1::~CModule1()
{
}


///////////////////////////////////////////////////////////////////////////////
// State Transitions 
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_IP_PI(CModule1)

///////////////////////////////////////////////////////////////////////////////
// State transition from PREOP to SAFEOP
//
// Initialize input parameters 
// Allocate memory
HRESULT CModule1::SetObjStatePS(PTComInitDataHdr pInitData)
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;
	IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(pInitData);
	
	//hr = SUCCEEDED(hr) ? InitAmsPort(m_spSrv, 0x3039) :  hr;
	// TODO: Add initialization code
	m_mapState[protocol::state_t::disconnected] = &CModule1::disconnected;
	m_mapState[protocol::state_t::init]			= &CModule1::init;
	m_mapState[protocol::state_t::idle]			= &CModule1::idle;
	m_mapState[protocol::state_t::ready]		= &CModule1::ready;
	m_mapState[protocol::state_t::active]		= &CModule1::active;
	m_mapState[protocol::state_t::emergency]	= &CModule1::emergency;
	m_mapState[protocol::state_t::recovery]		= &CModule1::recovery;
	m_mapState[protocol::state_t::error]		= &CModule1::error;

	transit(protocol::state_t::disconnected);

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from SAFEOP to op
//
// Register with other TwinCAT objects
HRESULT CModule1::SetObjStateSO()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	// TODO: Add any additional initialization


	// If following call is successful the CycleUpdate method will be called, 
	// possibly even before method has been left.
	hr = FAILED(hr) ? hr : AddModuleToCaller();

	// Cleanup if transition failed at some stage
	if (FAILED(hr))
	{
		RemoveModuleFromCaller();
	}

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from op to SAFEOP
HRESULT CModule1::SetObjStateOS()
{
	m_Trace.Log(tlVerbose, FENTERA);

	HRESULT hr = S_OK;

	RemoveModuleFromCaller();

	// TODO: Add any additional deinitialization

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from SAFEOP to PREOP
HRESULT CModule1::SetObjStateSP()
{
	HRESULT hr = S_OK;
	m_Trace.Log(tlVerbose, FENTERA);

	// TODO: Add deinitialization code

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///<AutoGeneratedContent id="ImplementationOf_ITcCyclic">
HRESULT CModule1::CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context)
{
	HRESULT hr = S_OK;
	
	run();
	if (elmos_.isAtLeastOneTrue([](slv::elmopp* e) { return e->hasError(); })) {
		transit(protocol::state_t::error);
	}


	return hr;
}
///</AutoGeneratedContent>

///////////////////////////////////////////////////////////////////////////////
HRESULT CModule1::AddModuleToCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);

	HRESULT hr = S_OK;
	if (m_spCyclicCaller.HasOID())
	{
		if (SUCCEEDED_DBG(hr = m_spSrv->TcQuerySmartObjectInterface(m_spCyclicCaller)))
		{
			if (FAILED(hr = m_spCyclicCaller->AddModule(m_spCyclicCaller, THIS_CAST(ITcCyclic))))
			{
				m_spCyclicCaller = NULL;
			}
		}
	}
	else
	{
		hr = ADS_E_INVALIDOBJID;
		SUCCEEDED_DBGT(hr, "Invalid OID specified for caller task");
	}

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
VOID CModule1::RemoveModuleFromCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);
	
	if (m_spCyclicCaller)
	{
		m_spCyclicCaller->RemoveModule(m_spCyclicCaller);
	}
	m_spCyclicCaller = NULL;

	m_Trace.Log(tlVerbose, FLEAVEA);
}

void CModule1::disconnected() {
	if (once()) {
		elmos_.run([](slv::elmopp* e) { e->disable(); });
		mainService_.write(protocol::rpc::frame_t(protocol::rpc::id::led::set, { protocol::rpc::param::led::color::none }));
		// led_.set(io::led::mode_t::solid, io::led::color_t::none);
	}
	
	if (isEvent(protocol::btn_t::connect)) {
		transit(protocol::state_t::init);
	}
	else {
		transit(protocol::state_t::disconnected);
	}
}

void CModule1::init() {
	mainService_.write(protocol::rpc::frame_t(protocol::rpc::id::led::set, { protocol::rpc::param::led::color::white }));
	// led_.set(io::led::mode_t::blink, io::led::color_t::white);

	// configure elmos and set intializing values, then attach to the manager if necessary
	for (int i = 0; i < 12; i++) {
		slv::elmopp::mode_t m = { &m_Outputs.Mode_of_operation[i] };
		slv::elmopp::type_t t = { &m_Outputs.ControlWord[i], &m_Inputs.StatusWord[i], &m_Inputs.ActualPosition[i], &m_Outputs.TargetPosition[i] };
		slv::elmopp::setting_t s = { &m_Outputs.Profile_Velocity[i], &m_Outputs.Profile_Acceleration[i], &m_Outputs.Profile_Deacceleration[i] };

		elmo_[i].configure(m, s, t);
		elmo_[i].initialize(slv::elmopp::mode_t{ &m_Setting.Mode }, slv::elmopp::setting_t{ &m_Setting.Velocity, &m_Setting.Acceleration, &m_Setting.Deacceleration });

		elmos_.attach(&elmo_[i]);
	}
	
	isDeviceOn() ? transit(protocol::state_t::idle) : transit(protocol::state_t::error);
}

void CModule1::idle() {
	if(once()) { 
		elmos_.run([](slv::elmopp* e) { e->disable(); });
		mainService_.write(protocol::rpc::frame_t(protocol::rpc::id::led::set, { protocol::rpc::param::led::color::white }));
		// led_.set(io::led::mode_t::solid, io::led::color_t::white);
	}

	if (isEvent(protocol::btn_t::disconnect)) {
		transit(protocol::state_t::disconnected);
	}
	else if (isEvent(protocol::btn_t::run)) {
		transit(protocol::state_t::ready);
	}
	else {
		transit(protocol::state_t::idle);
	}
}

void CModule1::ready() {
	if (once()) {
		mainService_.write(protocol::rpc::frame_t(protocol::rpc::id::led::set, { protocol::rpc::param::led::color::blue }));
		// led_.set(io::led::mode_t::blink, io::led::color_t::blue);
	}

	if (isEvent(protocol::btn_t::disconnect)) {
		transit(protocol::state_t::disconnected);
	}
	else {
		elmos_.run([](slv::elmopp* e) { e->enable(); });

		if (elmos_.is([](slv::elmopp* e) { return e->isEnabled(); })) {
			transit(protocol::state_t::active);
		}
		else {
			transit(protocol::state_t::ready);
		}
	}
}

void CModule1::active() {
	if (once()) {
		mainService_.write(protocol::rpc::frame_t(protocol::rpc::id::led::set, { protocol::rpc::param::led::color::green }));
		// led_.set(io::led::mode_t::solid, io::led::color_t::green);
	}

	elmos_.run([](slv::elmopp* e) { e->tryMove(); });

	if (mainService_.read().Data[0] > 0) {
		if (mainService_.read().Data[1] && elmos_.is([](slv::elmopp* e) { return e->isReached(); })) {
			elmos_.run([this](slv::elmopp* e) { e->disable(); }, &translation);
		}
		else {
			elmos_.run([](slv::elmopp* e) { if (!e->isReached()) e->stop();	});
		}
	}
	else if (mainService_.read().Data[0] == 0) {
		if (mainService_.read().Data[1]) {
			elmos_.run([](slv::elmopp* e) { if (!e->isEnabled()) e->enable(); });
		}
	}

	if (isEvent(protocol::btn_t::disconnect)) {
		transit(protocol::state_t::disconnected);
	}
	else if (isEvent(protocol::btn_t::emeregency)) {
		transit(protocol::state_t::emergency);
	}
	else if (isEvent(protocol::btn_t::idle)) {
		transit(protocol::state_t::idle);
	}
	else if (isEvent(protocol::btn_t::move)) {
		elmos_.run([this](slv::elmopp* e) { e->updatePos(receivedMove()); });
	}
	else if (isEvent(protocol::btn_t::halt)) {
		elmos_.run([](slv::elmopp* e) { e->stop(); });
	}
	else if (isEvent(protocol::btn_t::bending)) {
		elmos_.run([this](slv::elmopp* e) {	e->updatePos(receivedMove()); }, &bending);
	}
	else if (isEvent(protocol::btn_t::all_motors)) {
		elmos_.run([this](slv::elmopp* e) { e->updatePos(receivedMove()); });
	}
	else if (isEvent(protocol::btn_t::translation)) {
		elmos_.run([this](slv::elmopp* e) { e->updatePos(receivedMove()); }, &translation);
	}
}

void CModule1::emergency() {
	if (once()) {
		elmos_.run([](slv::elmopp* e) { e->disable(); });
		mainService_.write(protocol::rpc::frame_t(protocol::rpc::id::led::set, { protocol::rpc::param::led::color::yellow }));
		// led_.set(io::led::mode_t::blink, io::led::color_t::yellow);
	}

	if (isEvent(protocol::btn_t::disconnect)) {
		transit(protocol::state_t::disconnected);
	}
	else if (isEvent(protocol::btn_t::reset)) {
		transit(protocol::state_t::recovery);
	}
	else {
		transit(protocol::state_t::emergency);
	}
}

void CModule1::recovery() {
	static USHORT t_seed = 0;

	if (once()) {
		mainService_.write(protocol::rpc::frame_t(protocol::rpc::id::led::set, { protocol::rpc::param::led::color::yellow }));
		// led_.set(io::led::mode_t::blink, io::led::color_t::yellow);
	}

	elmos_.run([](slv::elmopp* e) { e->reset(); });

	if (isEvent(protocol::btn_t::disconnect)) {
		transit(protocol::state_t::disconnected);
	}
	else if (isDeviceOn() && elmos_.is([](slv::elmopp* e) { return !e->isEnabled(); })) {
		transit(protocol::state_t::idle);
	}
	else if (timeout(t_seed, 100)) {
		transit(protocol::state_t::error);
	}
	else {
		transit(protocol::state_t::recovery);
	}
}

void CModule1::error() {
	if (once()) {
		elmos_.run([](slv::elmopp* e) { e->disable(); });
		mainService_.write(protocol::rpc::frame_t(protocol::rpc::id::led::set, { protocol::rpc::param::led::color::red }));
		// led_.set(io::led::mode_t::solid, io::led::color_t::red);
	}

	if (isEvent(protocol::btn_t::reset)) {
		transit(protocol::state_t::recovery);
	}
	else {
		transit(protocol::state_t::error);
	}
}
