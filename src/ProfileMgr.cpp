#include "ProfileMgr.h"
#include "../../BlackBone/src/BlackBone/Misc/Utils.h"

#define CURRENT_PROFILE L"\\solomonCurrentProfile.xpr"

bool ProfileMgr::Save( const std::wstring& path /*= L""*/)
{
    try
    {
        auto filepath = path.empty() ? (blackbone::Utils::GetExeDirectory() + CURRENT_PROFILE) : path;

        acut::XmlDoc<wchar_t> xml;
        xml.create_document();

        for (auto& imgpath : _config.images)
            xml.append( L"solomonConfig.imagePath" ).value( imgpath );

        xml.set( L"solomonConfig.manualMapFlags", _config.mmapFlags );
        xml.set( L"solomonConfig.procName",       _config.procName.c_str() );
        xml.set( L"solomonConfig.hijack",         _config.hijack );
        xml.set( L"solomonConfig.unlink",         _config.unlink );
        xml.set( L"solomonConfig.erasePE",        _config.erasePE );
        xml.set( L"solomonConfig.close",          _config.close );
        xml.set( L"solomonConfig.krnHandle",      _config.krnHandle );
        xml.set( L"solomonConfig.injIndef",       _config.injIndef );
        xml.set( L"solomonConfig.processMode",    _config.processMode );
        xml.set( L"solomonConfig.injectMode",     _config.injectMode );
        xml.set( L"solomonConfig.delay",          _config.delay );
        xml.set( L"solomonConfig.period",         _config.period );
        xml.set( L"solomonConfig.skip",           _config.skipProc );
        xml.set( L"solomonConfig.procCmdLine",    _config.procCmdLine.c_str() );
        xml.set( L"solomonConfig.initRoutine",    _config.initRoutine.c_str() );
        xml.set( L"solomonConfig.initArgs",       _config.initArgs.c_str() );

        xml.write_document( filepath );
        
        return true;
    }
    catch (const std::runtime_error&)
    {
        return false;
    }
}

bool ProfileMgr::Load( const std::wstring& path /*= L""*/ )
{
    try
    {
        auto filepath = path.empty() ? (blackbone::Utils::GetExeDirectory() + CURRENT_PROFILE) : path;
        if (!acut::file_exists( filepath ))
            return false;

        acut::XmlDoc<wchar_t> xml;
        xml.read_from_file( filepath );

        // Load images in a safe way
        if(xml.has( L"solomonConfig.imagePath" ))
        {
            auto nodes = xml.all_nodes_named( L"solomonConfig.imagePath" );
            for (auto& node : nodes)
                _config.images.emplace_back( node.value() );
        }

        xml.get_if_present( L"solomonConfig.manualMapFlags",  _config.mmapFlags );
        xml.get_if_present( L"solomonConfig.procName",        _config.procName );
        xml.get_if_present( L"solomonConfig.hijack",          _config.hijack );
        xml.get_if_present( L"solomonConfig.unlink",          _config.unlink );
        xml.get_if_present( L"solomonConfig.erasePE",         _config.erasePE );
        xml.get_if_present( L"solomonConfig.close",           _config.close );
        xml.get_if_present( L"solomonConfig.krnHandle",       _config.krnHandle );
        xml.get_if_present( L"solomonConfig.injIndef",        _config.injIndef );
        xml.get_if_present( L"solomonConfig.processMode",     _config.processMode );
        xml.get_if_present( L"solomonConfig.injectMode",      _config.injectMode );
        xml.get_if_present( L"solomonConfig.delay",           _config.delay );
        xml.get_if_present( L"solomonConfig.period",          _config.period );
        xml.get_if_present( L"solomonConfig.skip",            _config.skipProc );
        xml.get_if_present( L"solomonConfig.procCmdLine",     _config.procCmdLine );
        xml.get_if_present( L"solomonConfig.initRoutine",     _config.initRoutine );
        xml.get_if_present( L"solomonConfig.initArgs",        _config.initArgs );

        return true;
    }
    catch (const std::runtime_error&)
    {
        return false;
    }
}
