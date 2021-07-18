using System;

namespace dotnetTest._svc
{
    [Flags]
    internal enum EngineOptions: uint
    {
        F_NONE = 0,

        /// <summary>
        /// Ignore case sensitivity when matching.
        /// </summary>
        F_ICASE         = 0x001,

        /// <summary>
        /// Collect additional data for the MatchResult.
        /// </summary>
        F_MATCH_RESULT  = 0x002,

        /// <summary>
        /// Do not finish on first match.
        /// </summary>
        F_MATCH_ALL     = 0x004,

#if _RXW_FEATURE_MATCH_MAP
        /// <summary>
        /// Collect the positions of all occurrences 
        /// between each presented metasymbol.
        /// </summary>
        F_MATCH_MAP     = 0x008,
#endif

        /// <summary>
        /// Use MS_ANYSP as [^/]* (legacy).
        /// Otherwise as [^c]* where `c` is a symbol from the next presented symbol after MS_ANYSP.
        /// </summary>
        F_LEGACY_ANYSP  = 0x080,
    }
}