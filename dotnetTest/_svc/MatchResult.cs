using System.Runtime.InteropServices;

namespace dotnetTest._svc
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct MatchResult
    {
        public static readonly nuint npos = nuint.MaxValue;

        /// <summary>
        /// Position of the first occurrence or MatchResult::npos.
        /// It also will be MatchResult::npos if not EngineOptions::F_MATCH_RESULT.
        /// </summary>
        public nuint start;

        /// <summary>
        /// Position of the last occurrence.
        /// Valid only if `MatchResult::start` != MatchResult::npos.
        /// </summary>
        public nuint end;
    }
}
