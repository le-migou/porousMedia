#pragma once

    struct
nonCopyable
{
    nonCopyable () = default;
    nonCopyable (nonCopyable const&) = delete;
};
